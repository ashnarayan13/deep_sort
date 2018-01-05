#!/usr/bin/env bash

python3 deep_sort_app.py --sequence_dir=/home/ashwath/fortiss/camera/ --detection_file=/home/ashwath/fortiss/camera/det/img1.npy --min_confidence=0.3 --nn_budget=100 --display=True

#python3 evaluate_motchallenge.py --mot_dir=/home/ashwath/fortiss/MOT16/test/ --detection_dir=./resources/detections/MOT16_POI_test/ --output_dir=./results/

#python3 generate_videos.py --mot_dir=/home/ashwath/fortiss/camera --result_dir=/home/ashwath/fortiss/camera --output_dir=/home/ashwath/PycharmProjects/deep_sort/results