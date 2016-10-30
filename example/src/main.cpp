#include "ofMain.h"
#include "ofxUnpackMotionJPEG.h"

class ofApp : public ofBaseApp
{
	public:
		ofxUnpackMotionJPEG mpg;
		vector<ofImage> img;

		void setup(){
			//mpg.setup("E0C0061611080222_00000011.mpg",true);
			mpg.setup("MVI_3572.AVI",true);
			img = mpg.getOfImages();
		}

		void update(){
		
		}

		void draw(){
			/*for(int i = 0; i < img.size(); i++)
			{
				img[i].draw(0,0);
			}*/
		}
};

int main()
{
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
