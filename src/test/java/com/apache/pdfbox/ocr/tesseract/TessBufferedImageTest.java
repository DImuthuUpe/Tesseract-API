package com.apache.pdfbox.ocr.tesseract;


import java.awt.image.BufferedImage;
import java.io.IOException;

import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.rendering.PDFRenderer;

import junit.framework.TestCase;

public class TessBufferedImageTest extends TestCase{
	TessBaseAPI api;
	public void testByteStram(){
		try {
			PDDocument document = PDDocument.load("src/main/resources/samples/pdf1.pdf");
			PDFRenderer renderer = new PDFRenderer(document);
			BufferedImage image = renderer.renderImage(0, 3);
			
			
			
			api = new TessBaseAPI();
			
			boolean init = api.init("src/main/resources/data", "eng");
			api.setBufferedImage(image);
			String text = api.getUTF8Text();
			System.out.println(text);
			api.end();
			assertEquals(init, true);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
