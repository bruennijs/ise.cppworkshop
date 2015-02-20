///////////////////////////////////////////////////////////
// MYTREE Linuxvariante

#include <sys/types.h>
#include <dirent.h>

#include <string>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

////////////////////////////////////////////

class Visitor
{
public:
	Visitor() {};
	~Visitor() {};
	
	virtual void visit(class Verzeichnis& v) = 0;

	virtual void visit(class Datei& d) = 0;
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
	typedef std::list<Datei *> 	Dateiliste;
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
	visitor.visit(*this);
	for (auto& d : liste)
		d->accept(visitor);
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
bool IsInstanceOf(const Datei* obj) noexcept {
	return dynamic_cast< const T* >( obj ) != nullptr;
}

//////////////////////////

class VisitorPrintFiles : public Visitor
{
public:
	VisitorPrintFiles() {};
	~VisitorPrintFiles() {};

	VisitorPrintFiles(VisitorPrintFiles&& rv) = delete;
	
	void visit(Verzeichnis& v) override
	{
		std::cout << "verz:" << v.GibName() << std::endl;	
	}

	void visit(Datei& d) override
	{
		std::cout << "datei:" << d.GibName() << std::endl;
	}
};

class VisitorCountFiles : public Visitor
{
public:
	VisitorCountFiles() {};
	~VisitorCountFiles() {};

	VisitorCountFiles(VisitorCountFiles&& rv) = delete;
	
	void visit(Verzeichnis& v) override
	{
		std::cout << v.GibName() << ":" << v.liste.size() << std::endl;
	}

	void visit(Datei& d) override
	{
		std::cout << "visit.datei" << std::endl;
	}
};


class VisitorRecursiveCountVerzeichnisse : public Visitor
{
public:
	VisitorRecursiveCountVerzeichnisse() {};
	~VisitorRecursiveCountVerzeichnisse() {};

	
	void visit(Verzeichnis& v) override
	{
		//m_countFiles += std::count_if(v.liste.begin(), v.liste.end(), [](Datei* d) { return IsInstanceOf<Verzeichnis>(d); });
		m_countFiles++;
	}

	void visit(Datei& d) override
	{
		
	}

	int getCount() {
		return m_countFiles;
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
	VisitorRecursiveCountVerzeichnisse vrcf;
	Verzeichnis root( verz );

	//root.accept(v);
	//root.accept(vcf);
	root.accept(vrcf);

	std::cout << "count of all files=" << vrcf.getCount() << std::endl;

	return 0;
}
