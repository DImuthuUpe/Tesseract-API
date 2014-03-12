package com.apache.pdfbox.ocr.tesseract;


import com.apache.pdfbox.ocr.tesseract.TessBaseAPI;
import junit.framework.TestCase;


public class TessBaseAPITest extends TestCase {
	
	public void testInit(){
		TessBaseAPI api =TessBaseAPI.getInstance();
		boolean init =api.init("/opt/local/share/", "eng");
		api.setImagePath("/Users/dimuthuupeksha/Documents/Academic/Tesseract-API/src/main/resources/samples/image4.TIF");
		//api.getUTF8Text();
		//api.end();
		System.out.println(api.getUTF8Text());
		assertEquals(true, init);
	}

}