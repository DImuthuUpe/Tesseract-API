package com.apache.pdfbox.ocr.tesseract;

import com.apache.pdfbox.ocr.tesseract.TessBaseAPI;
import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.Ignore;

import java.awt.image.BufferedImage;
import java.io.IOException;

import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.rendering.PDFRenderer;

public class TessBaseAPITest{

	@Test
	@Ignore
	public void testTIF(){
		TessBaseAPI api = new TessBaseAPI();
		boolean init =api.init("src/main/resources/data", "eng");
		api.setImagePath("src/main/resources/samples/image4.TIF");
		//api.getUTF8Text();
		//api.end();
		System.out.println(api.getUTF8Text());
		api.end();
		assertEquals(true, init);
	}
	
	@Test
	public void testBufferedImage(){
		try {
			PDDocument document = PDDocument.load("src/main/resources/samples/pdf1.pdf");
			PDFRenderer renderer = new PDFRenderer(document);
			BufferedImage image = renderer.renderImage(0, 3);
			
			TessBaseAPI api = new TessBaseAPI();
			boolean init = api.init("src/main/resources/data", "eng");
			api.setBufferedImage(image);
			String text = api.getUTF8Text();
			System.out.println(text);
			api.end();
			assertEquals(init, true);
			document.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Test
	public void testByteStram(){
		try {
			PDDocument document = PDDocument.load("src/main/resources/samples/pdf1.pdf");
			PDFRenderer renderer = new PDFRenderer(document);
			BufferedImage image = renderer.renderImage(0, 3);
			int width = image.getWidth();
			int height = image.getHeight();
			int bpp = 3;
			int bpl = width*3;
			
			TessBaseAPI api = new TessBaseAPI();
			byte data[] = api.getByteStream(image);
			boolean init = api.init("src/main/resources/data", "eng");
			api.setImage(data, width, height, bpp, bpl);
			String text = api.getUTF8Text();
			System.out.println(text);
			api.end();
			assertEquals(init, true);
			document.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Test
	public void testIterator() {
		try {
			PDDocument document = PDDocument.load("src/main/resources/samples/pdf1.pdf");
			PDFRenderer renderer = new PDFRenderer(document);
			BufferedImage image = renderer.renderImage(0, 3);
			TessBaseAPI api = new TessBaseAPI();
			boolean init = api.init("src/main/resources/data", "eng");
			api.setBufferedImage(image);
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
			document.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}