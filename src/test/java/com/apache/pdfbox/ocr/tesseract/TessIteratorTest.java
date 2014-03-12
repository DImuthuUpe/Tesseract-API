package com.apache.pdfbox.ocr.tesseract;


import junit.framework.TestCase;

public class TessIteratorTest extends TestCase {
	public void testIterator() {
		TessBaseAPI api = TessBaseAPI.getInstance();
		boolean init = api.init("/opt/local/share/", "eng");
		api.setImagePath("/Users/dimuthuupeksha/Documents/Academic/Tesseract-API/src/main/resources/samples/image4.TIF");
		api.getResultIterator();
		if (api.isResultIteratorAvailable()) {
			do {
				System.out.println(api.getWord().trim());
				String result = api.getBoundingBox();
				System.out.println(result);
			} while (api.resultIteratorNext());
		}

		//api.end();
		
		// System.out.println(api.getUTF8Text());
		

		assertEquals(true, init);
	}
}
