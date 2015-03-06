///////////////////////////////////////////////////////////
// MYTREE Linuxvariante

#include <sys/types.h>
#include <dirent.h>

#include <string>
#include <list>
#include <iostream>
using namespace std;

// Kompositstruktur
class Datei // Komponente
{
public:
	Datei( const string &n ) : name( n ) {}
	virtual ~Datei();
	const string & GibName() const { return name; }
	
	virtual void accept( class DateiBesucher &b ) = 0;

protected:
	string name;
};


class DateiBesucher
{
public:
	virtual ~DateiBesucher();
	virtual void visit( class Verzeichnis& ) = 0;
	virtual void visit( class RegulaereDatei& ) = 0;
	virtual void visit( class GeraeteDatei& ) = 0;
	virtual void visit( class KommunikationsDatei& ) = 0;
	virtual void visit( class SonstigeDatei& ) = 0;
};

class Verzeichnis :  public Datei  // Komposite
{
public:
	Verzeichnis( const string &n );
	~Verzeichnis();
	typedef std::list<Datei*> Dateiliste;
	Dateiliste liste;
	
	void accept( DateiBesucher &b );
};

class RegulaereDatei : public Datei  // Leaf
{
public:
	RegulaereDatei( const string &n ) : Datei( n ) {}
	void accept( DateiBesucher &b );
};

class GeraeteDatei : public Datei  // Leaf
{
public:
	GeraeteDatei( const string &n ) : Datei( n ) {}
	void accept( DateiBesucher &b );
};

class KommunikationsDatei : public Datei  // Leaf
{
public:
	KommunikationsDatei( const string &n ) : Datei( n ) {}
	void accept( DateiBesucher &b );
};

class SonstigeDatei : public Datei  // Leaf
{
public:
	SonstigeDatei( const string &n ) : Datei( n ) {}
	void accept( DateiBesucher &b );
};

class DateiBesucherLeerImpl : public DateiBesucher
{
public:
	void visit( Verzeichnis& ) override         {}
	void visit( RegulaereDatei& ) override      {}
	void visit( GeraeteDatei& ) override        {}
	void visit( KommunikationsDatei& ) override {}
	void visit( SonstigeDatei& ) override       {}
};

////////////////////////////////////////////////////////////////////////////////


Datei::~Datei() {}

DateiBesucher::~DateiBesucher() {}

void Verzeichnis::accept( DateiBesucher &b )  {
  b.visit(*this);
  for( auto d : liste )
  	d->accept( b );
}
void RegulaereDatei::accept( DateiBesucher &b )      { b.visit(*this); }
void GeraeteDatei::accept( DateiBesucher &b )        { b.visit(*this); }
void KommunikationsDatei::accept( DateiBesucher &b ) { b.visit(*this); }
void SonstigeDatei::accept( DateiBesucher &b )       { b.visit(*this); }


Verzeichnis::Verzeichnis( const string &n ) : Datei( n )
{
	struct dirent *pde;
	DIR *dirp = opendir( n.c_str() );
	if( dirp != NULL ) 
	{
		while( (pde = readdir( dirp )) != NULL )
		{
			std::string dname( pde->d_name );
			if( dname != "." && dname != ".." )
			{
				Datei *pd = 0;
				switch( pde->d_type )
				{
					case DT_REG:
						pd = new RegulaereDatei( dname );
						break;
					case DT_DIR:
						{
							std::string vn( n );
							if( vn[vn.size() - 1] != '/' )
								vn += "/";
							vn += dname;
							pd = new Verzeichnis( vn );
						}
						break;
					case DT_FIFO:
					case DT_SOCK:
						pd = new KommunikationsDatei( dname );
						break;
					case DT_CHR:
					case DT_BLK:
						pd = new GeraeteDatei( dname );
						break;				
					case DT_UNKNOWN:
					default:
						pd = new SonstigeDatei( dname );
						break;
				}
				if( pd )
					liste.push_back( pd );
			}
		}

		closedir(dirp);
	}
}

Verzeichnis::~Verzeichnis()
{
	for( Dateiliste::iterator it = liste.begin(); it != liste.end(); ++it )
		delete *it;
}

///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class VerzeichnisZaehler : public DateiBesucherLeerImpl
{
public:
	VerzeichnisZaehler() : n(0) {}
	void visit( Verzeichnis& ) override { n++; }
	
	long n;
};

int main( int argc, char *argv[] )
{
	using namespace std;

	string verz( argc > 1 ? argv[1] : "." );

	Verzeichnis root( verz );
	
	VerzeichnisZaehler z;
	root.accept(z);
	
	std::cout << z.n << std::endl;

	return 0;
}


