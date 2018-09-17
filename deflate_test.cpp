/* 
 * File:   deflate_test.cpp
 * Author: Yuxuan (Eric) Zheng
 *
 * Created on July 8, 2016, 10:52 AM
 */

#include "deflate.h"

/*
 * The main test bench file for both deflate and inflate core.
 *
 * It builds the input and compress/decompress the input to test the two cores.
 * Currently, the input size is limited to 3000 bytes. But it's easy to change it
 * to unlimited size. Just not use array for testing.
 */

int main(void)
{

    uint8_t decoder_output_array[3000], decoding_temp[3000];
    int size = 0;

    hls::stream<uint32_t> input, huffman_encoding_output;
    hls::stream<uint32_t> decoder_output;
    uint32_t input_word, output_word;

    /************************* build input ************************************/
    string temp =
        "To evaluate our prefetcher we modelled the system using the gem5 simulator [4] in full system mode with the setup "
        "given in table 2 and the ARMv8 64-bit instruction set. Our applications are derived from existing benchmarks and "
        "libraries for graph traversal, using a range of graph sizes and characteristics. We simulate the core breadth-first search "
        "based kernels of each benchmark, skipping the graph construction phase. Our first benchmark is from the Graph 500 community [32]. "
        "We used their Kronecker graph generator for both the standard Graph 500 search benchmark and a connected components "
        "calculation. The Graph 500 benchmark is designed to represent data analytics workloads, such as 3D physics "
        "simulation. Standard inputs are too long to simulate, so we create smaller graphs with scales from 16 to 21 and edge "
        "factors from 5 to 15 (for comparison, the Graph 500 toy input has scale 26 and edge factor 16). "
        "Our prefetcher is most easily incorporated into libraries that implement graph traversal for CSR graphs. To this "
        "end, we use the Boost Graph Library (BGL) [41], a C++ templated library supporting many graph-based algorithms "
        "and graph data structures. To support our prefetcher, we added configuration instructions on constructors for CSR "
        "data structures, circular buffer queues (serving as the work list) and colour vectors (serving as the visited list). This "
        "means that any algorithm incorporating breadth-first searches on CSR graphs gains the benefits of our prefetcher without "
        "further modification. We evaluate breadth-first search, betweenness centrality and ST connectivity which all traverse "
        "graphs in this manner. To evaluate our extensions for sequential access prefetching (section 3.5) we use PageRank "
        "and sequential colouring. Inputs to the BGL algorithms are a set of real world "
        "graphs obtained from the SNAP dataset [25] chosen to represent a variety of sizes and disciplines, as shown in table 4. "
        "All are smaller than what we might expect to be processing in a real system, to enable complete simulation in a realistic "
        "time-frame, but as figure 2(a) shows, since stall rates go up for larger data structures, we expect the improvements we "
        "attain in simulation to be conservative when compared with real-world use cases.";

    int i = 0;
    while (temp[i] != '\0')
    {
        i++;
        size++;
    }

    int copy_count = size / 4;
    copy_count++;

    for (int w = 0; w < copy_count; w++)
    {
        input_word = (temp[w * 4] << 24) | (temp[w * 4 + 1] << 16) | (temp[w * 4 + 2] << 8) | (temp[w * 4 + 3]);
        input.write(input_word);
    }

    cout << "//////////////////////////////////////////////////////////////" << endl;
    cout << "input size is " << size << endl;

    /************************* Deflate compression ****************************/

    Deflate(input, size, huffman_encoding_output);

    // copy stream output to a new array for counting size
    /*i = 0;
    while (!huffman_encoding_output.empty()) {
        huffman_encoding_output.read(output_word);
        decoding_temp[i * 4] = (output_word & 0xFF000000) >> 24;
        decoding_temp[i * 4 + 1] = (output_word & 0x00FF0000) >> 16;
        decoding_temp[i * 4 + 2] = (output_word & 0x0000FF00) >> 8;
        decoding_temp[i * 4 + 3] = (output_word & 0x000000FF);
        i++;
    }
    decoding_temp[i * 4] = '\0';
    decoding_temp[i * 4 + 1] = '\0';
    // Count for output size
    int p = 0;
    unsigned final_compressed_size = 0;
    while (decoding_temp[p] != '\0' || decoding_temp[p + 1] != '\0') {
        final_compressed_size++;
        p++;
    }
    cout << "Final compressed size after Huffman encoding is "
            << final_compressed_size << endl;
    cout << "The total compression ratio is "
            << ((double) size / (double) final_compressed_size) << endl << endl;*/

    /************************* Inflate decompression **************************/

    /******* The commented part is for testing the dynamic Inflate core. ******/

    /*
		hls::stream<uint32_t> d_input, d_output;
		uint32_t d_input_array[750];
		uint8_t d_output_array[3000];
		uint32_t d_output_word;
*/

    /*
		// Test Input 1:
		// The correct output should be: "As mentioned above,there are many kinds of wireless systems other than cellular."
		d_input_array[0] = 0x15CAD10D;
		d_input_array[1] = 0x80200C45;
		d_input_array[2] = 0xD155DE00; // from 8th is SQ1
		d_input_array[3] = 0xC61D1CA5;
		d_input_array[4] = 0xCA33104B;
		d_input_array[5] = 0x4968D5B0;
		d_input_array[6] = 0xBDF8717F; // from 13th is SQ2
		d_input_array[7] = 0x4EEEE6A8; // from 15th is LIT/DIST
		d_input_array[8] = 0xB428CD98;
		d_input_array[9] = 0x207B7BB8;
		d_input_array[10] = 0x44662764;
		d_input_array[11] = 0x56C506AE; // from 5th is "many "
		d_input_array[12] = 0x62C9D14E;
		d_input_array[13] = 0xBCA553E9;
		d_input_array[14] = 0x0E1F1EAC;
		d_input_array[15] = 0xD3FE1391; // from 6th is 0011 - distance 20 -> 0 011
		d_input_array[16] = 0xC57050F5;
		d_input_array[17] = 0x56E9EB07;
*/

    /*
		// Test Input 2:
		// The correct output should be:
		// "I tried to use this file to test the dynamic Huffman decoding core. But I am not sure whether the file will use dynamic trees."
		// (Well, I'm sure this test input is an example of dynamic Huffman encoding.)
		d_input_array[0] = 0x3d8d4b0a;
		d_input_array[1] = 0x84301005;
		d_input_array[2] = 0xf7738a77;
		d_input_array[3] = 0x020f312b;
		d_input_array[4] = 0x3d46485e;
		d_input_array[5] = 0xb4211fe8;
		d_input_array[6] = 0xee20de5e;
		d_input_array[7] = 0x83e0b6a0;
		d_input_array[8] = 0xaa36b80a;
		d_input_array[9] = 0x13bc6318;
		d_input_array[10] = 0xe18718b2;
		d_input_array[11] = 0x144ee034;
		d_input_array[12] = 0x7f0891ae;
		d_input_array[13] = 0x16aa44ac;
		d_input_array[14] = 0x23e71a1a;
		d_input_array[15] = 0x12634fd2;
		d_input_array[16] = 0x76c4ae5c;
		d_input_array[17] = 0xf01f8e0d;
		d_input_array[18] = 0xa1a27587;
		d_input_array[19] = 0x0d25ce83;
		d_input_array[20] = 0x8fa7537e;
		d_input_array[21] = 0x6ba79432;
		d_input_array[22] = 0x075fca95;
		d_input_array[23] = 0xb4e57703;
*/

    /*
        // Common for different dynamic Inflate test inputs
        for (int x = 0; x < 24; x++) {			// should change the loop boundary based on input
            d_input.write(d_input_array[x]);
        }
        inflate(d_input, d_output);
        // copy stream output to a new array for checking the result
        i = 0;
        while (!d_output.empty()) {
            d_output.read(d_output_word);
            d_output_array[i * 4] = (d_output_word & 0xFF000000) >> 24;
            d_output_array[i * 4 + 1] = (d_output_word & 0x00FF0000) >> 16;
            d_output_array[i * 4 + 2] = (d_output_word & 0x0000FF00) >> 8;
            d_output_array[i * 4 + 3] = (d_output_word & 0x000000FF);
            i++;
        }
        d_output_array[i * 4] = '\0';
        d_output_array[i * 4 + 1] = '\0';
        int c = 0;
        while (d_output_array[c] != '\0') {
            cout << d_output_array[c];
            c++;
        }
        cout << endl;
*/

    /** The normal inflate testing part. Mainly for static Huffman decoding **/

    inflate(huffman_encoding_output, decoder_output);
    // copy stream output to a new array for checking the result
    i = 0;
    while (!decoder_output.empty())
    {
        decoder_output.read(output_word);
        decoder_output_array[i * 4] = (output_word & 0xFF000000) >> 24;
        decoder_output_array[i * 4 + 1] = (output_word & 0x00FF0000) >> 16;
        decoder_output_array[i * 4 + 2] = (output_word & 0x0000FF00) >> 8;
        decoder_output_array[i * 4 + 3] = (output_word & 0x000000FF);
        i++;
    }
    decoder_output_array[i * 4] = '\0';
    decoder_output_array[i * 4 + 1] = '\0';

    /*************************** Compare Results *****************************/
    int t = 0;
    bool isFail = false;

    while (temp[t] != '\0' && decoder_output_array[t] != '\0' && !isFail)
    {
        if (temp[t] != decoder_output_array[t])
        {
            isFail = true;
            cout << "Deflate Fail!" << endl;
            cout << "at t = " << t << endl;
        }
        t++;
    }
    if (!isFail && temp[t] == '\0' && decoder_output_array[t] == '\0')
    {
        cout << "Deflate Succeed!" << endl;
    }
    else
    {
        if (!isFail)
        {
            cout << "Deflate Fail! Not the same length." << endl;
        }
    }
    cout << "//////////////////////////////////////////////////////////////" << endl;

    return 0;
}

/************* Original test file - use separated cores. For backup ***********/

//    uint8_t encoder_output[3000], decoder_output_array[3000],
//            huffman_decoding_output[3000], decoding_temp[3000];
//    int size = 0, compressed_size = 0, compressed_count = 0;
//    /**************************** LZ77 Encoding *******************************/
//    LZ77(input, size, encoder_output);
//
//    // Print out the compressed data
//    int offset, length;
//    int j = 0;
//    cout << endl << "LZ77 compressed stream is:" << endl << endl;
//    while (encoder_output[j] != '\0') {
//        if (encoder_output[j] == '@') {
//            offset = (encoder_output[j + 1] * 128) + encoder_output[j + 2];
//            length = encoder_output[j + 3];
//            cout << "@(" << offset << "," << length << ")";
//            j += 4;
//            compressed_size += 4;
//            compressed_count++;
//        } else {
//            cout << encoder_output[j];
//            j++;
//            compressed_size++;
//        }
//    }
//
//    cout << endl << endl << "compressed size after LZ77 is " << compressed_size << endl;
//    cout << "LZ77 compressed position count is " << compressed_count << endl;
//
//    /*************************** Huffman Encoding *****************************/
//    huffman(encoder_output, huffman_encoding_output);
//
//    // count for size
//    int p = 0;
//    cout << endl << endl;
//    unsigned final_compressed_size = 0;
//    while (huffman_encoding_output[p] != '\0' || huffman_encoding_output[p + 1] != '\0') {
//        //cout << (int) huffman_encoding_output[p] << " ";
//        final_compressed_size++;
//        p++;
//    }
//
//    cout << endl << endl;
//    cout << "Final compressed size after Huffman encoding is " << final_compressed_size << endl;
//    cout << "The total compression ratio is " << ((double) size / (double) final_compressed_size) << endl << endl;
//
//    /*************************** Huffman Decoding *****************************/
//    huffman_decoder(huffman_encoding_output, huffman_decoding_output);
//
//    /**************************** LZ77 Decoding *******************************/
//    LZ77_decoder(huffman_decoding_output, decoder_output);
//
//    /************************* Check Huffman Core *****************************/
//    int s = 0;
//    bool HisFail = false;
//
//    cout << endl;
//    while (encoder_output[s] != '\0' && huffman_decoding_output[s] != '\0' && !HisFail) {
//        if (encoder_output[s] != huffman_decoding_output[s]) {
//            HisFail = true;
//            cout << "Huffman Core Fail!" << endl;
//            cout << "at s = " << s << endl;
//        }
//        s++;
//    }
//    if (!HisFail && encoder_output[s] == '\0' && huffman_decoding_output[s] == '\0') {
//        cout << "Huffman Core Succeed!" << endl;
//    } else {
//        if (!HisFail) {
//            cout << "Huffman Core Fail! Not the same length." << endl;
//        }
//    }
//
//    /************************* Compare Result *********************************/
//    int t = 0;
//    bool isFail = false;
//
//    cout << endl;
//    while (input[t] != '\0' && decoder_output[t] != '\0' && !isFail) {
//        if (input[t] != decoder_output[t]) {
//            isFail = true;
//            cout << "LZ77 Fail!" << endl;
//            cout << "at t = " << t << endl;
//        }
//        t++;
//    }
//    if (!isFail && input[t] == '\0' && decoder_output[t] == '\0') {
//        cout << "LZ77 Succeed!" << endl;
//    } else {
//        if (!isFail) {
//            cout << "LZ77 Fail! Not the same length." << endl;
//        }
//    }

/*************************** End of old test file *****************************/