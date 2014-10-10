package com.apache.pdfbox.ocr.tesseract;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Native utilities.
 */
class NativeUtil {

  /**
   * Loads a native library from a resource in a JAR file.
   *
   * @param path resource path
   * @throws IOException if library could not be loaded
   */
  public static void loadLibraryResource(String path) throws IOException {
    String parts[] = path.split("\\.", 2);
    File temp = File.createTempFile(parts[0], "." + parts[1]);
    if (!temp.exists()) {
      throw new IOException("Error creating temporary file " + temp.getAbsolutePath());
    }
    temp.deleteOnExit();

    InputStream is = NativeUtil.class.getResourceAsStream(path);
    if (is == null) {
      throw new IOException("JAR file does not contain " + path);
    }

    byte[] buffer = new byte[1024];
    int length;
    OutputStream os = new FileOutputStream(temp);
    try {
      while ((length = is.read(buffer)) != -1) {
        os.write(buffer, 0, length);
      }
    } finally {
      os.close();
      is.close();
    }

    System.load(temp.getAbsolutePath());
  }
}
