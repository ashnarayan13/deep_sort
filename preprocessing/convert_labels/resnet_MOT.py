import argparse
import numpy as np
from decimal import *

def generate_detections(detection_file,output_dir):

   if(detection_file is None):
       raise ValueError('Please provide detection dir')

   else:
       detections_in = np.loadtxt(detection_file, delimiter=',')
       detections_out = []
       getcontext().prec = 6
       time_stamp = 0
       frame_idx = 1
       length = len(detections_in)
       for i in range(length):
           if time_stamp ==0:
               time_stamp = detections_in[i,0]
           elif time_stamp != detections_in[i,0]:
               time_stamp = detections_in[i,0]
               frame_idx = frame_idx+1
           detections_out.append([frame_idx,-1,detections_in[i,2],detections_in[i,1],np.abs(detections_in[i,4]-detections_in[i,2]),np.abs(detections_in[i,3]-detections_in[i,1]),0.83242,-1,-1,-1])
#original 1,2,3-1,4-2

   np.savetxt(output_dir+'/det_modified.npy',detections_out,fmt='%.2f',delimiter=',')






def parse_args():
   """Parse command line arguments.
   """
   parser = argparse.ArgumentParser(description="Re-ID feature extractor")
   parser.add_argument(
       "--detection_dir", help="Path to custom detections file ts wise ", default=None)
   parser.add_argument(
       "--output_dir", help="Output directory. Will be created if it does not"
       " exist.", default=None)
   return parser.parse_args()

if __name__ == "__main__":
   args = parse_args()
   generate_detections(args.detection_dir,args.output_dir)