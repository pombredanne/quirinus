import os
import re
import codecs
import struct

paths = [p for p in os.listdir(".") if not(p.endswith(".ct"))]
for src in os.listdir("."):
  if (src.endswith(".py")):
    continue
  dest = src.replace(".cpp", ".ct")
  print(src, dest)
  with codecs.open(src, "rb") as stream:
    data = stream.read()
  pattern = re.compile(b"\\s*(0x[0-9A-Ha-h]+),\\s*(0x[0-9A-Ha-h]+),", re.A)
  match = pattern.findall(data)
  if (match):
    with codecs.open(dest, "wb") as stream:
      for pair in match:
        byte = int(pair[0], 16)
        code = int(pair[1], 16)
        stream.write(struct.pack(">I", byte))
        stream.write(struct.pack(">I", code))
