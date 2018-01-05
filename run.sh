#!/usr/bin/env bash
#python3 deep_sort_app.py --sequence_dir=../MOT16/test/MOT16-03 --detection_file=./resources/detections/MOT16_POI_test/MOT16-03.npy --min_confidence=0.3 --nn_budget=100 --display=True

python3 evaluate_motchallenge.py --mot_dir=../MOT16/test/ --detection_dir=./resources/detections/MOT16_POI_test/ --output_dir=./results/