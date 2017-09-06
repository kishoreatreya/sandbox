package org.ka.Reflect;

/**
 * Created by kishoreatreya on 4/12/16.
 */

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.*;
import java.io.File;
import java.lang.reflect.*;


public class Parser
{
    private TargetConfig config = null;

    public Parser() throws Exception
    {
        config = new TargetConfig();

        buildFromResource();
    }

    private void buildFromResource() throws Exception
    {
        // The xml filenames have a very specific format
        try
        {
            ClassLoader classLoader = getClass().getClassLoader();

            File cfg = new File(classLoader.getResource("org/ka/Reflect/xp80a0.xml").getFile());

            // Now that we've loaded the xml file. Parse it into a DOM object
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(cfg);

            doc.getDocumentElement().normalize();

            // We will rely on Java Reflection methodology to build this class using xml field names
            // array attributes will be used to set an array parameter
            //
            // We will loop through all the nodes collected in the DOM
            //

            // Get the class
            Class<?> c = config.getClass();

            System.out.println(doc.getChildNodes().item(0));
            for(int count = 0; count < doc.getChildNodes().getLength(); count++)
            {
                Node n = doc.getChildNodes().item(count);
                if(n.getNodeType() == Node.ELEMENT_NODE)
                {
                    if(n.getNodeName().equals("device"))
                    {
                        continue;
                    }

                    // If this is a class node
                    if(!n.hasAttributes())
                    {
                        // Inspect the TargetConfig using reflection and fetch the right sub class
                        for(Field s : c.getFields())
                        {
                            System.out.println(s.toString());
                        }
                    }
                }
            }

        }
        catch (Exception ioe)
        {
            System.out.println("Error: Filename " + "xp80a0.xml" + " not found. Possible that device type xp80a0 doesn't exist");
        }

    }

    private void buildAndWalk(NodeList list)
    {

    }

}
