///////////////////////////////////////////////////////////
// MYTREE Linuxvariante

#include <sys/types.h>
#include <dirent.h>

#include <string>
#include <list>
#include <iostream>
using namespace std;

class Verzeichnis;
class Datei;

class Visitor
{
public:
	Visitor() {};
	~Visitor() {};
	
	virtual void visit(Verzeichnis* v) = 0;

	virtual void visit(Datei* d) = 0;
};

// Kompositstruktur
class Datei // Komponente
{
public:
	Datei( const string &n ) : name( n ) {}
	virtual ~Datei();
	const string & GibName() const { return name; }

	virtual void accept(Visitor& visitor)
	{
	}
protected:
	string name;
};

class Verzeichnis :  public Datei  // Komposite
{
public:
	Verzeichnis( const string &n );
	~Verzeichnis();
	typedef std::list<Datei *> Dateiliste;
	Dateiliste liste;	

	void accept(Visitor& visitor) override;
};


///////////////////////

class RegulaereDatei : public Datei  // Leaf
{
public:
	RegulaereDatei( const string &n ) : Datei( n ) {}
};

class GeraeteDatei : public Datei  // Leaf
{
public:
	GeraeteDatei( const string &n ) : Datei( n ) {}
};

class KommunikationsDatei : public Datei  // Leaf
{
public:
	KommunikationsDatei( const string &n ) : Datei( n ) {}
};

class SonstigeDatei : public Datei  // Leaf
{
public:
	SonstigeDatei( const string &n ) : Datei( n ) {}
};

////////////////////////////////////////////////////////////////////////////////


Datei::~Datei() {}


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

void Verzeichnis::accept(Visitor& visitor)
{
	visitor.visit(this);
	for (auto& d : liste)
		d->accept(visitor);
}

///////////////////////////////////////////////////////////////////////////////

class VisitorPrintFiles : public Visitor
{
public:
	VisitorPrintFiles() {};
	~VisitorPrintFiles() {};

	VisitorPrintFiles(VisitorPrintFiles&& rv) = delete;
	
	void visit(Verzeichnis* v) override
	{
		std::cout << "verz:" << v->GibName() << std::endl;	
	}

	void visit(Datei* d) override
	{
		std::cout << "datei:" << d->GibName() << std::endl;
	}
};

class VisitorCountFiles : public Visitor
{
public:
	VisitorCountFiles() {};
	~VisitorCountFiles() {};

	VisitorCountFiles(VisitorCountFiles&& rv) = delete;
	
	void visit(Verzeichnis* v) override
	{
		std::cout << v->GibName() << ":" << v->liste.size() << std::endl;
	}

	void visit(Datei* d) override
	{
		std::cout << "visit.datei" << std::endl;
	}
};


class VisitorRecursiveCountFiles : public Visitor
{
public:
	VisitorRecursiveCountFiles() {};
	~VisitorRecursiveCountFiles() {};

	
	void visit(Verzeichnis* v) override
	{
		m_countFiles += v->liste.size();
		for (auto& d : v->liste)
		{
			visit(d);
		}
	}

	void visit(Datei* d) override
	{
		
	}

private:
	int m_countFiles = 0;
};

///////////////////////////////

int main( int argc, char *argv[] )
{
	using namespace std;

	string verz( argc > 1 ? argv[1] : "." );

	VisitorPrintFiles v;
	VisitorCountFiles vcf;
	Verzeichnis root( verz );

	//root.accept(v);
	root.accept(vcf);

	return 0;
}


