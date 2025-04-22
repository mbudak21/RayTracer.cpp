#ifndef _Defaults_H_
#define _Defaults_H_

#include "Color.h"

// Source for material values: http://devernay.free.fr/cours/opengl/materials.html
// I found this source from a LEGO forum lol. 
namespace ColorDefaults {
	const Color White(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(1.0f, 1.0f, 1.0f), Vec3f(1.0f, 1.0f, 1.0f));
	const Color Black(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 0.0f));
	const Color Red(Vec3f(1.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
	const Color Green(Vec3f(0.0f, 1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	const Color Blue(Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 0.0f, 1.0f));

	const Color RedRealistic(Vec3f(0.15f, 0.0f, 0.0f), Vec3f(0.7f, 0.0f, 0.0f), Vec3f(0.3f, 0.3f, 0.3f));
	const Color GreenRealistic(Vec3f(0.0f, 0.15, 0.0f), Vec3f(0.0f, 0.7f, 0.0f), Vec3f(0.3f, 0.3f, 0.3f));
	const Color BlueRealistic(Vec3f(0.0f, 0.0f, 0.15), Vec3f(0.0f, 0.0f, 0.7f), Vec3f(0.3f, 0.3f, 0.3f));

	const Color Gold(Vec3f(0.24725f, 0.1995f, 0.0745f), Vec3f(0.75164f, 0.60648f, 0.22648f), Vec3f(0.628281f, 0.555802f, 0.366065f));
	const Color Copper(Vec3f(0.19125f, 0.0735f, 0.0225f), Vec3f(0.7038f, 0.27048f, 0.0828f), Vec3f(0.256777f, 0.137622f, 0.086014f));
	const Color Silver(Vec3f(0.19225f, 0.19225f, 0.19225f), Vec3f(0.50754f, 0.50754f, 0.50754f), Vec3f(0.508273f, 0.508273f, 0.508273f));
	const Color Emerald(Vec3f(0.0215f, 0.1745f, 0.0215f), Vec3f(0.07568f, 0.61424f, 0.07568f), Vec3f(0.633f, 0.727811f, 0.633f));
	const Color Jade(Vec3f(0.135f, 0.2225f, 0.1575f), Vec3f(0.54f, 0.89f, 0.63f), Vec3f(0.316228f, 0.316228f, 0.316228f));
	const Color Obsidian(Vec3f(0.05375f, 0.05f, 0.06625f), Vec3f(0.18275f, 0.17f, 0.22525f), Vec3f(0.332741f, 0.328634f, 0.346435f));
	const Color Pearl(Vec3f(0.25f, 0.20725f, 0.20725f), Vec3f(1.0f, 0.829f, 0.829f), Vec3f(0.296648f, 0.296648f, 0.296648f));
	const Color Ruby(Vec3f(0.1745f, 0.01175f, 0.01175f), Vec3f(0.61424f, 0.04136f, 0.04136f), Vec3f(0.727811f, 0.626959f, 0.626959f));
	const Color Turquoise(Vec3f(0.1f, 0.18725f, 0.1745f), Vec3f(0.396f, 0.74151f, 0.69102f), Vec3f(0.297254f, 0.30829f, 0.306678f));
	const Color Brass(Vec3f(0.329412f, 0.223529f, 0.027451f), Vec3f(0.780392f, 0.568627f, 0.113725f), Vec3f(0.992157f, 0.941176f, 0.807843f));
	const Color Bronze(Vec3f(0.2125f, 0.1275f, 0.054f), Vec3f(0.714f, 0.4284f, 0.18144f), Vec3f(0.393548f, 0.271906f, 0.166721f));
	const Color Chrome(Vec3f(0.25f, 0.25f, 0.25f), Vec3f(0.4f, 0.4f, 0.4f), Vec3f(0.774597f, 0.774597f, 0.774597f));
	const Color RedPlastic(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.5f, 0.0f, 0.0f), Vec3f(0.7f, 0.6f, 0.6f));
	const Color WhitePlastic(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.55f, 0.55f, 0.55f), Vec3f(0.7f, 0.7f, 0.7f));
	const Color YellowPlastic(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.5f, 0.5f, 0.0f), Vec3f(0.6f, 0.6f, 0.5f));
	const Color GreenPlastic(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.1f, 0.35f, 0.1f), Vec3f(0.45f, 0.55f, 0.45f));
	const Color CyanPlastic(Vec3f(0.0f, 0.1f, 0.06f), Vec3f(0.0f, 0.50980392f, 0.50980392f), Vec3f(0.50196078f, 0.50196078f, 0.50196078f));
	const Color BlackPlastic(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.01f, 0.01f, 0.01f), Vec3f(0.5f, 0.5f, 0.5f));
	const Color BlackRubber(Vec3f(0.02f, 0.02f, 0.02f), Vec3f(0.01f, 0.01f, 0.01f), Vec3f(0.4f, 0.4f, 0.4f));
	const Color CyanRubber(Vec3f(0.0f, 0.05f, 0.05f), Vec3f(0.4f, 0.5f, 0.5f), Vec3f(0.04f, 0.7f, 0.7f));
	const Color GreenRubber(Vec3f(0.0f, 0.05f, 0.0f), Vec3f(0.4f, 0.5f, 0.4f), Vec3f(0.04f, 0.7f, 0.04f));
	const Color RedRubber(Vec3f(0.05f, 0.0f, 0.0f), Vec3f(0.5f, 0.4f, 0.4f), Vec3f(0.7f, 0.04f, 0.04f));
	const Color WhiteRubber(Vec3f(0.05f, 0.05f, 0.05f), Vec3f(0.5f, 0.5f, 0.5f), Vec3f(0.7f, 0.7f, 0.7f));
	const Color YellowRubber(Vec3f(0.05f, 0.05f, 0.0f), Vec3f(0.5f, 0.5f, 0.4f), Vec3f(0.7f, 0.7f, 0.04f));
}

namespace MaterialDefaults {
	// Full flat 
	const Material BlackFlat(ColorDefaults::Black, 0.0f);
	const Material WhiteFlat(ColorDefaults::White, 0.0f);
	const Material RedFlat(ColorDefaults::Red, 0.0f);
	const Material GreenFlat(ColorDefaults::Green, 0.0f);
	const Material BlueFlat(ColorDefaults::Blue, 0.0f);

	const Material RedRealistic(ColorDefaults::RedRealistic, 0.2f);
	const Material GreenRealistic(ColorDefaults::GreenRealistic, 0.7f);
	const Material BlueRealistic(ColorDefaults::BlueRealistic, 0.3f);



	
	// Metals
	const Material Gold(ColorDefaults::Gold, 0.4f);
	const Material Copper(ColorDefaults::Copper, 0.1f);
	const Material Silver(ColorDefaults::Silver, 0.4f);
	
	// Crystals
	const Material Emerald(ColorDefaults::Emerald, 0.6f);
	const Material Jade(ColorDefaults::Jade, 0.1f);
	const Material Obsidian(ColorDefaults::Obsidian, 0.3f);
	const Material Pearl(ColorDefaults::Pearl, 0.088f);
	const Material Ruby(ColorDefaults::Ruby, 0.6f);
	const Material Turquoise(ColorDefaults::Turquoise, 0.1f);
	
	// Alloys
	const Material Brass(ColorDefaults::Brass, 0.21794872f);
	const Material Bronze(ColorDefaults::Bronze, 0.2f);
	const Material Chrome(ColorDefaults::Chrome, 0.6f);
	
	// Plastics
	const Material RedPlastic(ColorDefaults::RedPlastic, 0.25f);
	const Material WhitePlastic(ColorDefaults::WhitePlastic, 0.25f);
	const Material YellowPlastic(ColorDefaults::YellowPlastic, 0.25f);
	const Material GreenPlastic(ColorDefaults::GreenPlastic, 0.25f);
	const Material CyanPlastic(ColorDefaults::CyanPlastic, 0.25f);
	const Material BlackPlastic(ColorDefaults::BlackPlastic, 0.25f);

	// Rubbers
	const Material BlackRubber(ColorDefaults::BlackRubber, 0.078125f);
	const Material CyanRubber(ColorDefaults::CyanRubber, 0.078125f);
	const Material GreenRubber(ColorDefaults::GreenRubber, 0.078125f);
	const Material RedRubber(ColorDefaults::RedRubber, 0.078125f);
	const Material WhiteRubber(ColorDefaults::WhiteRubber, 0.078125f);
	const Material YellowRubber(ColorDefaults::YellowRubber, 0.078125f);

	// Mirror
	const Material Mirror(ColorDefaults::White, 0.0f, 1.0f);
	
	// // Ful
	// const Material FlatBlack(ColorDefaults::Black, 0.0f, 0.0f);
	// const Material FlatWhite(ColorDefaults::White, 0.0f, 0.0f);
	
	// // Metals
	// const Material Gold(ColorDefaults::Gold, 51.2f, 0.85f);
	// const Material Copper(ColorDefaults::Copper, 12.8f, 0.5f);
	// const Material Silver(ColorDefaults::Silver, 51.2f, 0.8f);
	
	// // Crystals
	// const Material Emerald(ColorDefaults::Emerald, 0.6f, 0.3f);
	// const Material Jade(ColorDefaults::Jade, 0.1f, 0.3f);
	// const Material Obsidian(ColorDefaults::Obsidian, 0.3f, 0.2f);
	// const Material Pearl(ColorDefaults::Pearl, 0.088f, 0.2f);
	// const Material Ruby(ColorDefaults::Ruby, 0.6f, 0.3f);
	// const Material Turquoise(ColorDefaults::Turquoise, 0.1f, 0.25f);
	
	// // Alloys
	// const Material Brass(ColorDefaults::Brass, 0.21794872f, 0.6f);
	// const Material Bronze(ColorDefaults::Bronze, 0.2f, 0.5f);
	// const Material Chrome(ColorDefaults::Chrome, 0.6f, 0.9f);
	
	// // Plastics
	// const Material RedPlastic(ColorDefaults::RedPlastic, 0.25f, 0.05f);
	// const Material WhitePlastic(ColorDefaults::WhitePlastic, 0.25f, 0.05f);
	// const Material YellowPlastic(ColorDefaults::YellowPlastic, 0.25f, 0.05f);
	// const Material GreenPlastic(ColorDefaults::GreenPlastic, 0.25f, 0.05f);
	// const Material CyanPlastic(ColorDefaults::CyanPlastic, 0.25f, 0.05f);
	// const Material BlackPlastic(ColorDefaults::BlackPlastic, 0.25f, 0.03f);

	// // Rubbers
	// const Material BlackRubber(ColorDefaults::BlackRubber, 0.078125f, 0.02f);
	// const Material CyanRubber(ColorDefaults::CyanRubber, 0.078125f, 0.02f);
	// const Material GreenRubber(ColorDefaults::GreenRubber, 0.078125f, 0.02f);
	// const Material RedRubber(ColorDefaults::RedRubber, 0.078125f, 0.02f);
	// const Material WhiteRubber(ColorDefaults::WhiteRubber, 0.078125f, 0.02f);
	// const Material YellowRubber(ColorDefaults::YellowRubber, 0.078125f, 0.02f);
}


#endif
