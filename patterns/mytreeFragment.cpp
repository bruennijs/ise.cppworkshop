///////////////////////////////////////////////////////////
// MYTREE 

#define _CRT_SECURE_NO_DEPRECATE	// For MS VC++ 8 and newer
#define _CRT_NONSTDC_NO_DEPRECATE	// dito. undocumented define

#include <string>
#include <list>
using namespace std;
#include <windows.h>

// Hilfsfunktion
const string right( const string &s, unsigned int n );

// Kompositstruktur
class Datei // Komponente
{
public:
	Datei( const string &n ) : name( n ) {}
	virtual ~Datei();
	const string & GibName() const { return name; }

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


private:
	void lesen();	
};

class UnbestimmteDatei : public Datei  // Leaf
{
public:
	UnbestimmteDatei( const string &n ) : Datei( n ) {}
};

class EXEDatei : public Datei  // Leaf
{
public:
	EXEDatei( const string &n ) : Datei( n ) {}
};

class DLLDatei : public Datei  // Leaf
{
public:
	DLLDatei( const string &n ) : Datei( n ) {} 
};

class TextDatei : public Datei  // Leaf
{
public:
	TextDatei( const string &n ) : Datei( n ) {}
};

////////////////////////////////////////////////////////////////////////////////


Datei::~Datei() {}


Verzeichnis::Verzeichnis( const string &n ) : Datei( n )
{
	char *p = new char[MAX_PATH];
	GetCurrentDirectory( MAX_PATH, p );
	if( SetCurrentDirectory( n.c_str() ) )
		lesen();
	SetCurrentDirectory( p );
	delete [] p;
}

Verzeichnis::~Verzeichnis()
{
	for( Dateiliste::iterator it = liste.begin(); it != liste.end(); ++it ) 
		delete *it;
}

void Verzeichnis::lesen()
{
	WIN32_FIND_DATA data;
	HANDLE fh = FindFirstFile( "*", &data );
	if( fh != INVALID_HANDLE_VALUE )
	{
		do
		{
			string filename( data.cFileName );
			
			if( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				if( filename != string(".") && filename != string("..") )
				{
					Verzeichnis *v = new Verzeichnis( filename );
					liste.push_back( v );
				}
			}
			else
			{
				Datei *d;
				
				string ext( right(filename,4) );

				if( strcmpi( ext.c_str(), ".exe" ) == 0 )
					d = new EXEDatei( filename );
				else if( strcmpi( ext.c_str(), ".dll" ) == 0 )
					d = new DLLDatei( filename );
				else if( strcmpi( ext.c_str(), ".txt" ) == 0  )
					d = new TextDatei( filename );
				else
					d = new UnbestimmteDatei( filename );

				liste.push_back( d );
		
			}
		} while( FindNextFile( fh, &data ) );

		FindClose( fh );
	}
}

const string right( const string &s, unsigned int n )
{
	if( n <= s.length() )
		return s.substr( s.length() - n, n);
	return string();
}


///////////////////////////////////////////////////////////////////////////////


int main( int argc, char *argv[] )
{
	using namespace std;

	string verz( argc > 1 ? argv[1] : "." ); 
	
	Verzeichnis root( verz );


	return 0;
}




