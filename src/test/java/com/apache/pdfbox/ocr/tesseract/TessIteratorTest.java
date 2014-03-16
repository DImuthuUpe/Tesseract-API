package com.apache.pdfbox.ocr.tesseract;


import junit.framework.TestCase;

public class TessIteratorTest extends TestCase {
	public void testIterator() {
		TessBaseAPI api = new TessBaseAPI();
		boolean init = api.init("src/main/resources/data", "eng");
		api.setImagePath("src/main/resources/samples/image4.TIF");
		api.getResultIterator();
		if (api.isResultIteratorAvailable()) {
			do {
				System.out.println(api.getWord().trim());
				String result = api.getBoundingBox();
				System.out.println(result);
			} while (api.resultIteratorNext());
		}
		api.end();
		assertEquals(init, true);
	}
}
