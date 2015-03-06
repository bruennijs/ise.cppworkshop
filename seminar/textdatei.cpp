#include <cstdio>
#include <cassert>
#include <list>
#include <utility>
#include <iostream>

class Textdatei
{
public:
	Textdatei( const char *name );
	~Textdatei();
	
	Textdatei( Textdatei && );
	Textdatei( const Textdatei& ) = delete;
	Textdatei& operator=( const Textdatei& ) = delete;
	
	void schreiben( const char* txt );
	bool gueltig() const { return f != 0; }
private:
	FILE *f;
};

Textdatei::Textdatei( const char *name )
{
	f = fopen( name, "wt" );
}
Textdatei::Textdatei( Textdatei &&d ) : f(d.f)
{
	d.f = 0;
}
Textdatei::~Textdatei()
{
	if( f != 0 )
	{
		fclose( f );
	}
}
	
void Textdatei::schreiben( const char* txt )
{
	assert( f != 0 );
	fputs( txt, f );
}

void f( std::list<Textdatei> &d )
{
	for( auto i = d.begin(); i != d.end(); ++i )
		i->schreiben( "Eine lange Zeile Text.\n" );
}

int main()
{
	Textdatei d1( "test1.txt" );
	Textdatei d2( "test2.txt" );
	if( d1.gueltig() && d2.gueltig() )
	{
		std::list<Textdatei> dateien;
	
		dateien.push_back( std::move(d1) );
		dateien.push_back( std::move(d2) );
		dateien.push_back( Textdatei("test3.txt") );
		dateien.emplace_back( "test4.txt" );
		
		f( dateien );
	}

}


