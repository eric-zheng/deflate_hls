# deflate algorithm

June 29. Currently, the algorithm uses LZ77 and static Huffman encoding. The compression ratio is around 1.6x

July 8. Upload the files for dynamic Huffman encoding. Still need to write into the output stream. Will switch to hardware core now.

July 18. Add the Inflate core. The inflate core can support dynamic Huffman decoding. Currently, the test input was hard-coded because the core is big endian. I will change the core to little endian later. Then, the core can basically decode all files following the standard.

July 21. Add comments and documentation on the files.

July 22. Modified the dynamic Huffman decoding process to little-endian. Currently, the static inflate uses Big-Endian (corresponding to the Deflate core). The dynamic inflate uses Little-Endian, which means that it can decode the standard zip file, provided that the zip file was parsed to have only the real compressed data (no zip header inside).

Aug. 3. Organized the entire project. Added several new comments. It's the latest version in the summer 2016.
