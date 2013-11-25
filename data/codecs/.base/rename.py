import os
import re
import codecs
import struct

paths = [p for p in os.listdir(".") if not(p.endswith(".ct"))]
for src in os.listdir("."):
  if (src.endswith(".py")):
    continue
  dest = src.replace(".cpp", ".ct")
  with codecs.open(src, "rb") as stream:
    data = stream.read()
  pattern = re.compile(b"\\s*(0x[0-9A-Ha-h]+),\\s*(0x[0-9A-Ha-h]+),", re.A)
  match = pattern.findall(data)
  if (match):
    name = src.replace(".cpp", "")
    name = name.replace("_", "-")
    if (name.startswith("MAC")):
      name = name.lower()
    elif (name.startswith("ATARIST")):
      name = "AtariST"
    elif (name.startswith("KPS9566")):
      name = "KPS 9566"
    elif (name.startswith("BIG5")):
      name = "Big5"
    name = name.encode("UTF-8")
    print(name)
    with codecs.open(dest, "wb") as stream:
      stream.write(name)
      stream.write(b'\0')
      for pair in match:
        byte = int(pair[0], 16)
        code = int(pair[1], 16)
        stream.write(struct.pack(">I", byte))
        stream.write(struct.pack(">I", code))
""_u8
""_u16
""_u32

""_f64
""_f80
""_QF
""_F
