import argparse
import os
import xml.etree.ElementTree as ET

def generate_detections(input_dir, output_file):
    xml_files = []
    save_file = open(output_file,'w')
    for filename in os.listdir(input_dir):
        xml_files.append(str(os.path.join(input_dir, filename)))
    counter = 1
    for filename in xml_files:
        xmin = []
        ymin = []
        xmax = []
        ymax = []
        tree = ET.parse(str(filename))
        #print(tree.getroot())
        root = tree.getroot()
        #print(root.attrib)
        for child in root:
            for sibling in child:
                if str(sibling.tag) == 'bndbox':
                    print(len(sibling))
                    xmin.append(float(sibling[0].text))
                    ymin.append(float(sibling[1].text))
                    xmax.append(float(sibling[2].text))
                    ymax.append(float(sibling[3].text))
                    for bnd in sibling:
                        print(bnd.tag, bnd.text)
        for i in range(0,len(xmin)):
            save_file.write("%d,-1,%f,%f,%f,%f,0.83,-1,-1,-1\n"%(counter,xmin[i],ymin[i],xmax[i]-xmin[i],ymax[i]-ymin[i]))

    print(xml_files)
    save_file.close()

def main():
   """Parse command line arguments.
   """
   parser = argparse.ArgumentParser(description="Re-ID feature extractor")
   parser.add_argument("--detection_dir")
   parser.add_argument("--output_files")
   return parser.parse_args()

if __name__ == "__main__":
   args = main()
   generate_detections(args.detection_dir,args.output_files)