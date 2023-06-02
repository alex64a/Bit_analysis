#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <conio.h>


#ifndef endl
#define endl "\n"
#endif

#include "filt.h"
#include "filt.cpp"

using namespace std;


// WAVE PCM soundfile format (you can find more in https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ )
typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;
header_file wav;



void echo(char* path) {



    fstream filin(path, ios::in|ios::binary);
    fstream fileout("output_echo.wav",ios::out| ios::binary);

    int eco_rate = 10000;
    short int temp;
    short int ch[eco_rate], ch2[eco_rate];
    int i,j;

    for(i=0; i<eco_rate; i++)
    ch2[i] = 0;

            while(!filin.eof()) {

                for(i=0; i<eco_rate && !filin.eof(); i++)
                filin.read((char*)&ch[i], sizeof(short int));
                for(i=0; i<eco_rate; i++)   {

                temp  = ch[i];
                ch[i]+=ch2[i];
                fileout.write((char*)&ch[i], sizeof(short int));
                ch2[i] = temp;
                                            }

                                }

     filin.close();
     fileout.close();

            }


void Low_pass_filter(char* path) {


    Filter *my_filter;
    my_filter = new Filter(LPF, 51, 44.1 , 1.0);
    short samp_dat;
	double out_val;
	int num_read;

	FILE *fd_in, *fd_out;
    fd_in = fopen(path, "r");
	fd_out = fopen("output_LPF.wav", "w");


	int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)
	int count = 0;						// For counting number of frames in wave file.
	short int buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	int nb;

    if (fd_in)
	{
		fread(meta, 1, sizeof(header), fd_in);
		fwrite(meta,1, sizeof(*meta), fd_out);

 	while (!feof(fd_in))
		{
			nb = fread(buff16,1,BUFSIZE,fd_in);		// Reading data in chunks of BUFSIZE
			//cout << nb <<endl;
			count++;	// Incrementing Number of frames


			/* Insert your processing code here*/
            while(1){
			num_read = fread(&samp_dat, sizeof(short), 1, fd_in);
            if(num_read != 1) break;
            out_val = my_filter->do_sample( (double) samp_dat );
            samp_dat = (short) out_val;
            fwrite(&samp_dat, sizeof(short), 1, fd_out);
            			// Writing read data into output file


            }

    fwrite(buff16,1,nb,fd_out);

		}

	}

    fclose(fd_in);
	fclose(fd_out);
	delete my_filter;


}


void Band_pass_filter(char* path) {



    Filter *my_filter;
    my_filter = new Filter(BPF, 51, 44.1, 1.0, 2.0);
    short samp_dat;
	double out_val;
	int num_read;

	FILE *fd_in, *fd_out1;
    fd_in = fopen(path, "r");
	fd_out1 = fopen("output_BPF.wav", "w");


	int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)
	int count = 0;						// For counting number of frames in wave file.
	short int buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	int nb;

    if (fd_in)
	{
		fread(meta, 1, sizeof(header), fd_in);
		fwrite(meta,1, sizeof(*meta), fd_out1);

 	while (!feof(fd_in))
		{
			nb = fread(buff16,1,BUFSIZE,fd_in);		// Reading data in chunks of BUFSIZE
			//cout << nb <<endl;
			count++;	// Incrementing Number of frames


			/* Insert your processing code here*/
            while(1){
			num_read = fread(&samp_dat, sizeof(short), 1, fd_in);
            if(num_read != 1) break;
            out_val = my_filter->do_sample( (double) samp_dat );
            samp_dat = (short) out_val;
            fwrite(&samp_dat, sizeof(short), 1, fd_out1);
            			// Writing read data into output file


            }

    fwrite(buff16,1,nb,fd_out1);

		}

	}

    fclose(fd_in);
	fclose(fd_out1);
	delete my_filter;


}


void High_pass_filter(char* path) {




    Filter *my_filter;
    my_filter = new Filter(HPF, 51, 44.1, 3.0);
    short samp_dat;
	double out_val;
	int num_read;

	FILE *fd_in, *fd_out2;
    fd_in = fopen(path, "r");
	fd_out2 = fopen("output_HPF.wav", "w");


	int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)
	int count = 0;						// For counting number of frames in wave file.
	short int buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	int nb;

    if (fd_in)
	{
		fread(meta, 1, sizeof(header), fd_in);
		fwrite(meta,1, sizeof(*meta), fd_out2);

 	while (!feof(fd_in))
		{
			nb = fread(buff16,1,BUFSIZE,fd_in);		// Reading data in chunks of BUFSIZE
			//cout << nb <<endl;
			count++;	// Incrementing Number of frames


			/* Insert your processing code here*/
            while(1){
			num_read = fread(&samp_dat, sizeof(short), 1, fd_in);
            if(num_read != 1) break;
            out_val = my_filter->do_sample( (double) samp_dat );
            samp_dat = (short) out_val;
            fwrite(&samp_dat, sizeof(short), 1, fd_out2);
            			// Writing read data into output file


            }

    fwrite(buff16,1,nb,fd_out2);

		}

	}

    fclose(fd_in);
	fclose(fd_out2);
	delete my_filter;


}



int main(int argc, char *argv[])
{


	char select;


    cout << "Please select 1-4 for desired effect:\n 1.echo\n 2.LPF\n 3.BPF\n 4.HPF\n\n";
    cin >> select;


     if(select == '1') echo(argv[1]);

     if(select == '2') Low_pass_filter(argv[1]);

     if(select == '3') Band_pass_filter(argv[1]);

     if(select == '4') High_pass_filter(argv[1]);


}
