#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

myText="abca";
text2print = myText;

// the data for writing one letter in Baudot
currentBaudotCode = "";
// some positioning stuff
fx = 25; // your size to the right
fy = 25; // your size between circles of one letter (to y)

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	// delete screen
	ofBackground (255);
	// show current word
	ofSetColor(0);
	ofFill();
	showTheWordAsBaudot();
}

void testApp::showTheWordAsBaudot(void)
{
// here Baudot circles are made
// go through the word you entered letter by letter
x=0;
y=0;
for (int i = 0 ; i < myText.length() ; i++) {
	// get the Baudot Code for the letter
	currentBaudotCode = (string) GetBaudCode((char)myText[i]);
	// if not found
	if (currentBaudotCode == "")
	{
		// not found: show a ? sign for the whole letter
		//println(myText.charAt(i)+ " not found in baudotAlphabet.");
		//fill(0);
		//text ("?", 20+i*fx, y+20+3*fy );
	}
	else
	{
		// found
		// check line break
		// check line break
		if (i > 3 && i % 55 == 0) {
			if ( y==0) {
				x-=fx*55; // begin of line
				y+=300; // next line
			}
			else if ( y==300) {
				x-=fx*55; // begin of line
				y+=300; // next line
			}
		}
		// interprete the Baudot Code again letter by letter as saying: big or small cirlce
		for (int j = 0 ; j < currentBaudotCode.length() ; j++) {
			// if a
			if (currentBaudotCode[j] == 'a')
			{
				// big cirlce
				ofEllipse (x+20+i*fx, y+20+j*fy, 18, 18);
				ofSetColor(0);
				ofFill();
			}
			// if b
			else if (currentBaudotCode[j] == 'b')
			{
				// small cirlce
				ofEllipse (x+20+i*fx, y+20+j*fy, 12, 12);
				ofSetColor(0);
				ofFill();
			}
			// if c
			else if (currentBaudotCode[j] == 'c')
			{
				// small cirlce
				//ofEllipse (20+i*fx, 20+j*fy, 18, 18);
			}
			else
			{
				// error: wrong character
				// show one ? instead of a circle
				//text ("?", x+20+i*fx, y+20+j*fy );
				//println ("error in "+ currentBaudotCode	+ " for " + currentBaudotCode.charAt(j)	+ " with " + myText.charAt(i));
			}
		}//for
	}
} 


}

string testApp::GetBaudCode(char ascii_code)
{
	return baudotLookup[ascii_code-97];
}


void testApp::SaveImage(void)
{
	ofSaveScreen("test.png");
}

void testApp::Print(void)
{
	/* print using the command line */
	system("rundll32.exe c:\\Windows\\System32\\shimgvw.dll, ImageView_PrintTo c:\\temp\\a.png \"HP Officejet Pro K850 Series\"");  

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	// add letter to the word
	myText += key;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}