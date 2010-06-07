#include <SFML/Audio.hpp>

#include <iostream>
#include <stdexcept>

#include "xm.h"

int main( int argc, char ** argv )
{

	try
	{
		
		sf::SoundBuffer buf;
		sound::XmSound snd;
		sound::XmSound::Samples samp;
	
		if (!snd.Load( "src/sound/Second_try_015.xm" ))
			throw std::runtime_error( "SHIT IS FUCKED UP" );
		samp = snd.GetSamples();

		buf.LoadFromSamples( samp.samples, samp.sz / 2, 1, 44100 );

	}

	catch ( std::runtime_error err )
	{

		std::cout << "Status report: " << err.what() << std::endl;
		return 1;

	}

	return 0;

}

