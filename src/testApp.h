#pragma once

#include "ofMain.h"

const string baudotLookup[] = {
	/*"a"*/  "aabccc"	
	/*"b"*/, "acbcaa"
	/*"c"*/, "cabaac"
	/*"d"*/, "acbcac"
	/*"e"*/, "acbccc"
	/*"f"*/, "acbaac"
	/*"g"*/, "cabcaa"
	/*"h"*/, "ccbaca"
	/*"i"*/, "cabacc"
	/*"j"*/, "aabcac"
	/*"k"*/, "aabaac"
	/*"l"*/, "cabcca"
	/*"m"*/, "ccbaaa"
	/*"n"*/, "ccbaac"
	/*"o"*/, "ccbcaa"
	/*"p"*/, "cabaca"
	/*"q"*/, "aabaca"
	/*"r"*/, "cabcac"
	/*"s"*/, "acbacc"
	/*"t"*/, "ccbcca"
	/*"u"*/, "aabacc"
	/*"v"*/, "cabaaa"
	/*"w"*/, "aabcca"
	/*"x"*/, "acbaaa"
	/*"y"*/, "acbaca"
	/*"z"*/, "acbcca"
	/*" "*/, "ccbacc"
};


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void showTheWordAsBaudot(string);
		string GetBaudCode(char);
		void Print(void);
		void SaveImage(void);
		void ConvertTextFile(string);

		// what you enter (use backspace and type)
		string myText;
		string text2print;


		// the data for writing one letter in Baudot
		string currentBaudotCode;
		// some positioning stuff
		int fx; // your size to the right
		int fy; // your size between circles of one letter (to y)

		int x, y;

		ofFbo fbo;

};
