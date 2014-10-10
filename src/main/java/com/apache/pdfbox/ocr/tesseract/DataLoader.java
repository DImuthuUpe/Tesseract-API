/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.apache.pdfbox.ocr.tesseract;

import java.io.*;

public class DataLoader {
    public static String tessdataTempFolder;
    public static String getDataPath(String language) throws IOException{

        if(tessdataTempFolder==null||!(new File(tessdataTempFolder)).exists()){ //This is to avoid creating multiple temp data directories.
            File temp = File.createTempFile("tessdata","");
            if (!temp.exists()) {
                throw new IOException("Error creating temporary file " + temp.getAbsolutePath());
            }
            if(!(temp.delete())){
                throw new IOException("Could not delete temp file: " + temp.getAbsolutePath());
            }

            if(!(temp.mkdir())){
                throw new IOException("Could not create temp directory: " + temp.getAbsolutePath());
            }
            tessdataTempFolder = temp.getAbsolutePath();
            temp.deleteOnExit();
        }
        File tessDataFile = new File(tessdataTempFolder+"/tessdata");
        tessDataFile.mkdir();
        File langFile = new File(tessDataFile.getAbsolutePath()+"/"+language+".traineddata");

        InputStream is = DataLoader.class.getResourceAsStream("/data/tessdata/"+language+".traineddata");
        if (is == null) {
            throw new IOException("Training file does not contain " + language+".traineddata");
        }

        byte[] buffer = new byte[1024];
        int length;
        OutputStream os = new FileOutputStream(langFile);
        try {
            while ((length = is.read(buffer)) != -1) {
                os.write(buffer, 0, length);
            }
        } finally {
            os.close();
            is.close();
        }
        return tessdataTempFolder;
    }

}
