#include "ofMain.h"
#include "FreeImage.h"

class ofxUnpackMotionJPEG 
{
	public:
		vector<ofImage> container;

		void setup(string mUrl, bool dfile=false, bool debug=false)
		{
			ofFile file(mUrl, ofFile::ReadOnly, true);
			ofBuffer buffer(file);

			char MAGIG_NUMBER[3];
			int startIndex = 0;

			MAGIG_NUMBER[0] = 0xff;
			MAGIG_NUMBER[1] = 0xd8;
			MAGIG_NUMBER[2] = 0xff;
			int num = 0;
			for ( int i = 0, ii = buffer.size(); i < ii; ++i )
			{
				if ((char)buffer.getData()[i]   == (char)MAGIG_NUMBER[0] && 
				    (char)buffer.getData()[i+1] == (char)MAGIG_NUMBER[1] && 
				    (char)buffer.getData()[i+2] == (char)MAGIG_NUMBER[2]) 
				{
					if (i > 0 && startIndex != 0 && i < buffer.size())
					{
						ofBuffer buf;
						stringstream st;
						for(int k = startIndex; k < i; k++)
						{
							st<<buffer.getData()[k];
						}
						buf.set(st.str());
						buf.end();

						bool wrtf;
						string name = "IMG_"+ofToString(num)+".jpg";

						if(dfile) 
						{
                                                        wrtf = ofBufferToFile("jpg/"+name, buf); 
							string pathjpg = ofToDataPath("jpg/",true)+name;
							string pathpng = ofToDataPath("png/",true)+name+".png";
							ofImage img;
							img.load(pathjpg);
							container.push_back(img);

							FIBITMAP* bitmap = Loader(pathjpg.c_str(),BMP_DEFAULT);
							if(bitmap)
							{
								ofLog()<<"File FreeImage_Load() success.";
								FreeImage_Save(FIF_PNG, bitmap, pathpng.c_str());
								FreeImage_Unload(bitmap);
							}
							else
								ofLog()<<"File FreeImage_Load() error.";
						}
						if(debug)
						{
							ofLog()<<"from: "<<startIndex<<" - to: "<<i
							       <<" - size-buffer: "<<buffer.size()
							       <<" - state-file: "<<wrtf<<" - name: "<<name;
						}


						num++;
					}
					startIndex = i;
				}
			}
		}

		vector<ofImage> getOfImages()
		{
			return container;
		}

	private:
		FIBITMAP* Loader(const char* lpszPathName, int flag) {
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			ofLog()<<lpszPathName;	 
 			fif = FreeImage_GetFileType(lpszPathName, 0);
			ofLog()<<"FreeImage_GetFileType(): "<<fif;
			if(fif == FIF_UNKNOWN) {
				ofLog()<<"UNKNOWN";
 			 	fif = FreeImage_GetFIFFromFilename(lpszPathName);
			}
			if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
				ofLog()<<"FIF SUPPORT";
			 	FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, flag);
				 return dib;
			}
			return NULL;
		}
};
