package com.apache.pdfbox.ocr.tesseract;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import junit.framework.TestCase;

public class TessByteSteamTest extends TestCase{
	TessBaseAPI api;
	public void testByteStram(){
		try {
			BufferedImage image = ImageIO.read(new File("/Users/dimuthuupeksha/Documents/Academic/Tesseract-API/src/main/resources/samples/image1.jpg"));
			int width = image.getWidth();
			int height = image.getHeight();
			int bpp = 3;
			int bpl = width*3;
			byte data[] = getByteStream(image);
			api = TessBaseAPI.getInstance();
			boolean init = api.init("/opt/local/share/", "eng");
			api.setImage(data, width, height, bpp, bpl);
			String text = api.getUTF8Text();
			System.out.println(text);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public byte[] getByteStream(BufferedImage image){
		int width = image.getWidth();
		int height = image.getHeight();
		
		byte[] data = new byte[width*height*3];
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Color c = new Color(image.getRGB(j,i));
				int red = c.getRed();
				int green = c.getGreen();
				int blue = c.getBlue();
				data[((width*i+j)*3)] = (byte)blue;
				data[((width*i+j)*3)+1] = (byte)green;
				data[((width*i+j)*3)+2] = (byte)red;
				
				
				//System.out.println(red+" "+green+" "+blue);
			}
		}
		return data;
	}
}
