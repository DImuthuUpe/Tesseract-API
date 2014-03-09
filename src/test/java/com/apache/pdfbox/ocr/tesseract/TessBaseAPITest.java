package com.apache.pdfbox.ocr.tesseract;


import com.apache.pdfbox.ocr.tesseract.TessBaseAPI;
import junit.framework.TestCase;


public class TessBaseAPITest extends TestCase {
	public void testInit(){
		TessBaseAPI api =new TessBaseAPI();
		boolean init =api.init("/opt/local/share/", "eng");
		api.setImagePath("/Users/dimuthuupeksha/Documents/Academic/Tesseract-API/src/main/resources/samples/image4.TIF");
		System.out.println(api.getUTF8Text());
		assertEquals(true, init);
		
	}

}