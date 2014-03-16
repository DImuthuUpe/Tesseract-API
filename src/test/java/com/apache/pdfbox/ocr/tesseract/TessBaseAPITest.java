package com.apache.pdfbox.ocr.tesseract;


import com.apache.pdfbox.ocr.tesseract.TessBaseAPI;
import junit.framework.TestCase;


public class TessBaseAPITest extends TestCase {
	
	public void testInit(){
		TessBaseAPI api = new TessBaseAPI();
		boolean init =api.init("src/main/resources/data", "eng");
		api.setImagePath("src/main/resources/samples/image4.TIF");
		//api.getUTF8Text();
		//api.end();
		System.out.println(api.getUTF8Text());
		api.end();
		assertEquals(true, init);
	}

}