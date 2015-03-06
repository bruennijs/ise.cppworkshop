
#include <iostream>

typedef char EVENT;

class Phase
{
public:
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void handle( EVENT e ) = 0;
	Phase *folgeZustand;
};

class Betriebszustand
{
public:
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void handle( EVENT e ) = 0;
	Betriebszustand *folgeZustand;
};

class Rot : public Phase
{
public:
	void enterState() { std::cout << "ROT" << std::endl; }
	void exitState() {}
	void handle( EVENT e ) {}
};

class RotGelb : public Phase
{
public:
	void enterState() { std::cout << "ROT-GELB" << std::endl; }
	void exitState() {}
	void handle( EVENT e ) {}
};

class Gruen : public Phase
{
public:
	void enterState() { std::cout << "GRUEN" << std::endl; }
	void exitState() {}
	void handle( EVENT e ) {}
};

class Gelb : public Phase
{
public:
	void enterState() { std::cout << "GELB" << std::endl; }
	void exitState() {}
	void handle( EVENT e ) {}
};

class Regelnd : public Betriebszustand
{
public:
	Regelnd()
	{
		rot.folgeZustand = &rotgelb;
		rotgelb.folgeZustand = &gruen;
		gruen.folgeZustand = &gelb;
		gelb.folgeZustand = &rot;
		aktuellerZustand = &rot;
	}
	void enterState()
	{
		aktuellerZustand = &rot;
		aktuellerZustand->enterState();
	}
	void exitState() 
	{
		aktuellerZustand->exitState();
	}
	void handle( EVENT e )
	{
		switch( e )
		{
			case 'p':
				aktuellerZustand->exitState();
				aktuellerZustand = aktuellerZustand->folgeZustand;
				aktuellerZustand->enterState();
				break;
			default:
				aktuellerZustand->handle( e );
				break;
		}
	}
private:
	Rot rot;
	RotGelb rotgelb;
	Gruen gruen;
	Gelb gelb;
	Phase *aktuellerZustand;
};

class Blinkend : public Betriebszustand
{
public:
	void enterState() { std::cout << "blinkend" << std::endl; }
	void exitState() {}
	void handle( EVENT e ) {}
};

class Ampel
{
public:
	Ampel()
	{
		regelnd.folgeZustand = &blinkend;
		blinkend.folgeZustand = &regelnd;
		aktuellerZustand = &regelnd;
		aktuellerZustand->enterState();
	}
	~Ampel()
	{
		aktuellerZustand->exitState();
	}
	
	bool handle( EVENT e )
	{
		switch( e )
		{
			case 'b':
				aktuellerZustand->exitState();
				aktuellerZustand = aktuellerZustand->folgeZustand;
				aktuellerZustand->enterState();
				break;
			case 'q':
			case 'x':
				return false;
			default:
				aktuellerZustand->handle( e );
				break;
		}
		return true;
	}
	
private:
	Regelnd regelnd;
	Blinkend blinkend;
	Betriebszustand *aktuellerZustand;
};


int main()
{
	Ampel ampel;
	
	std::cout << sizeof(Ampel) << std::endl;
	
	EVENT e = 0x00;
	do
	{
		std::cin >> e;
	} while( ampel.handle(e) );

	return 0;
}


