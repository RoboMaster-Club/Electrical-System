import sys
import struct
import csv

"""
Decode binary log file and output as csv file
"""

data_format = 'Iffff?ffffff??'
packet_length = struct.calcsize(data_format)
log_path = sys.argv[1]
csv_path = sys.argv[2]

with open(csv_path, "w") as csv_fp:
    out = csv.writer(csv_fp)
    with open(log_path, 'rb') as log_fp:
        while True:
            chunk = log_fp.read(packet_length)
            if chunk == '' or len(chunk) < packet_length:
                break
            measurement = struct.unpack(data_format, chunk)
            print(measurement)
            out.writerow(measurement)
