#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetFrameRate(60);   
	fbo.allocate( 512, 512, GL_RGBA,0);

	myText="abca";
	text2print = myText;

	// the data for writing one letter in Baudot
	currentBaudotCode = "";
	// some positioning stuff
	fx = 25; // your size to the right
	fy = 25; // your size between circles of one letter (to y)
	MorseCodeSetup();

	//TwitterSetup();

}

void testApp::MorseCodeSetup(void)
{
	currentIndex = 0;

	//Path to the comma delimited file
	string filePath = "morse.csv";
	
	//Use a ofTrueTypeFont for scalable text
	font.loadFont("frabk.ttf", 122);
	
	//Load file placed in bin/data
	ofFile file(filePath);
	
	if(!file.exists()){
		ofLogError("The file " + filePath + " is missing");
	}
	
	ofBuffer buffer(file);
	
	//Read file line by line
	while (!buffer.isLastLine()) {
		string line = buffer.getNextLine();
		
		//Split line into strings
		vector<string> words = ofSplitString(line, ",");
		
		//Store strings into a custom container
		MorseCodeSymbol symbol;
		symbol.character = words[0];
		symbol.code = words[1];
		
		//Save MorseCodeSymbols for later
		morseCodeSymbols.push_back(symbol);
		
		//Debug output
		ofLogVerbose("symbol.character: " + symbol.character);
		ofLogVerbose("symbol.code: " + symbol.code);
	}
	
	//Load our Morse code sounds
	player.setup(); 
}

void testApp::TwitterSetup(void)
{
	twitter.connect(
		"YOUR_USERNAME"
		,"YOUR_PASSWORD"
		,"stream.twitter.com"
		,"/1/statuses/filter.json?track=YOUR_FILTER_KEYWORD"
	);
}

string testApp::TwitterCheckForTweet(void)
{
	string tweetText = "";
	
	while(twitter.hasNewTweets()) {
		ofxTweet t = twitter.getNextTweet();
		cout << "text:" << t.getText() << endl;
		tweetText = t.getText();
		cout << "avatar:" << t.getAvatar() << endl;
		cout << "---" << endl;
	}

 return tweetText;
}

//--------------------------------------------------------------
void testApp::update(){
	//Update our MorseCodePlayer with the app
	player.update();

	//TwitterCheckForTweet();
}

//--------------------------------------------------------------
void testApp::draw(){

	// delete screen
	ofBackground (255);
	// show current word
	ofSetColor(0);
	ofFill();
	showTheWordAsBaudot(myText);

}

void testApp::showTheWordAsBaudot(string inputText)
{
// here Baudot circles are made
// go through the word you entered letter by letter
x=0;
y=0;
for (int i = 0 ; i < inputText.length() ; i++) {
	// get the Baudot Code for the letter
	currentBaudotCode = (string) GetBaudCode((char)inputText[i]);
	// if not found
	if (currentBaudotCode == "")
	{
		// not found
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
				
			}
		}//for
	}
} 


}

string testApp::GetBaudCode(char ascii_code)
{
	return baudotLookup[ascii_code-97];
}

void testApp::ConvertTextFile(string fileName)
{
	// this is our buffer to stroe the text data
    ofBuffer buffer = ofBufferFromFile("test.txt");
    
	if(buffer.size()) { 
        
		/* declare and start the FBO*/
		
		
		fbo.begin();
		glPixelStorei(GL_PACK_ALIGNMENT, 1); 


        // we now keep grabbing the next line
        // until we reach the end of the file
        while(buffer.isLastLine() == false) {
            
            // move on to the next line
            string line = buffer.getNextLine();
            
            // make sure its not a empty line
            if(line.empty() == false) {


				// delete screen
				ofBackground (255);
				// show current word
				ofSetColor(0);
				ofFill();
				showTheWordAsBaudot(line);
			}
            
            // print out the line
            cout << line << endl;
            
        }

		/* save the fbo to file */
		ofImage imgSaver;
		imgSaver.allocate(fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR);
		imgSaver.setUseTexture(false);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);  
		unsigned char *pixels;
		pixels = new unsigned char[((int)fbo.getWidth())*((int)fbo.getHeight())*3];
		glReadPixels(0, 0, fbo.getWidth(), fbo.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels);
		imgSaver.setFromPixels(pixels, fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR);
		imgSaver.mirror(0,0);
		imgSaver.saveImage("data/caps/test.png");
		fbo.end();
		delete pixels;
        
    } 



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
	if (key == 'p')
	{
		SaveImage();
	}
	if (key == 'f')
	{
		ConvertTextFile("");
	}
	MorseCodeKeyPressed(key);

}

void testApp::MorseCodeKeyPressed(int key)
{
	//Create a comparable string from an int
	string myKey;
	myKey = (char) key;
	myKey = ofToUpper(myKey);
	
	for (int i=0; i<morseCodeSymbols.size(); i++) {
		if (morseCodeSymbols[i].character == myKey){
			currentSymbol = morseCodeSymbols[i];
			player.playCode(currentSymbol.code);
		}
		
	} 
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