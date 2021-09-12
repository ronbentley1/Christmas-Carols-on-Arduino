//
// Ron D Bentley, Stafford, UK, September 2021
//
// Christmas Carols with Arduino - based on 'let's make music' Arduino sketch
// by same author.
//
// Uses a simple circuit connecting an 8 ohm speaker on digital pin 11...that's all!
// Merry Christmas!!
//
// This example and code is in the public domain and
// may be used without restriction and without warranty.
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// % Music/tone data and functions... %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//
// Tempos, by common musical names
//
#define  grave          40
#define  largo          46
#define  lento          52
#define  adagio         56
#define  larghetto      60
#define  adagietto      66
#define  andante        72
#define  andantino      80
#define  maestroso      88
#define  moderato      100
#define  allegretto    104
#define  animato       120
#define  allegro       132
#define  allegro_assai 144
#define  vivace        160
#define  presto        184
#define  prestissimo   208

//
// Public constants - reflects the 'pitches.h' file,
// but with a different (shortened) note naming convention.
// The values are the frequencies (hz) of the notes.
//
#define B0  31
#define C1  33
#define CS1 35
#define DF1 35
#define D1  37
#define DS1 39
#define EF1 39
#define E1  41
#define F1  44
#define FS1 46
#define GF1 46
#define G1  49
#define GS1 52
#define AF1 52
#define A1  55
#define AS1 58
#define BF1 58
#define B1  62
#define C2  65
#define CS2 69
#define DF2 69
#define D2  73
#define DS2 78
#define EF2 78
#define E2  82
#define F2  87
#define FS2 93
#define GF2 93
#define G2  98
#define GS2 104
#define AF2 104
#define A2  110
#define AS2 117
#define BF2 117
#define B2  123
#define C3  131
#define CS3 139
#define DF3 139
#define D3  147
#define DS3 156
#define EF3 156
#define E3  165
#define F3  175
#define FS3 185
#define GF3 185
#define G3  196
#define GS3 208
#define AF3 208
#define A3  220
#define AS3 233
#define BF3 233
#define B3  247
#define C4  262 // <--------- middle C
#define CS4 277
#define DF4 277
#define D4  294
#define DS4 311
#define EF4 311
#define E4  330
#define F4  349
#define FS4 370
#define GF4 370
#define G4  392
#define GS4 415
#define AF4 415
#define A4  440
#define AS4 466
#define BF4 466
#define B4  494
#define C5  523
#define CS5 554
#define DF5 554
#define D5  587
#define DS5 622
#define EF5 622
#define E5  659
#define F5  698
#define FS5 740
#define GF5 740
#define G5  784
#define GS5 831
#define AF5 831
#define A5  880
#define AS5 932
#define BF5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define DF6 1109
#define D6  1175
#define DS6 1245
#define EF6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define GF6 1480
#define G6  1568
#define GS6 1661
#define AF6 1661
#define A6  1760
#define AS6 1865
#define BF6 1865
#define B6  1976
#define C7  2093
#define CS7 2217
#define DF7 2217
#define D7  2349
#define DS7 2489
#define EF7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define GF7 2960
#define G7  3136
#define GS7 3322
#define AF7 3322
#define A7  3520
#define AS7 3729
#define BF7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define DF8 4435
#define D8  4699
#define DS8 4978
#define EF8 4978

#define speaker                11     // digital pin number for speaker/buzzer

float default_tempo = float(animato); // default tempo - beats per minute
float current_tempo = default_tempo;
float timings[7];                     // holds timings for each defined note/rest time value

//
// Standard note/rest duration definitions, set in the set_tempo function
//
#define semib       timings[0] // semi briev       - 4 beats
#define dot_minim   timings[1] // dotted mini      - 3 beats
#define minim       timings[2] // minim            - 2 beats
#define crot        timings[3] // crotchet         - 1 beat
#define quav        timings[4] // quaver           - 1/2 beat
#define semiq       timings[5] // semi quaver      - 1/4 beat
#define demi_semiq  timings[6] // demi semi quaver - 1/8 beat

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Carols data...
// Setup play list data
//

#define num_carols  10

// Forward references for music score functions
// which are defined at end of the sketch to avoid clutter...
void we_wish_you_a_merry_christmas();
void o_come_all_ye_faithful();
void away_in_a_manger();
void ding_dong_merrily();
void good_king_wenceslas();
void the_first_nowell();
void the_holly_and_the_ivy();
void we_three_kings();
void silent_night();
void jingle_bells();

//
// Declare pointer array and preset with addresses 
// of each of the carol score functions.
// Note that the oder of the presets is not important
// as the play_list array is constantly randomised 
// by the shuffle_play_list function.
uint16_t (*play_list[num_carols])() = {
  we_wish_you_a_merry_christmas,
  o_come_all_ye_faithful,
  away_in_a_manger,
  ding_dong_merrily,
  good_king_wenceslas,
  the_first_nowell,
  the_holly_and_the_ivy,
  we_three_kings,
  silent_night,
  jingle_bells
};
// End of carols data
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//
// Shuffle the play_list randomly
//
void shuffle_play_list() {
  uint8_t swap_with;
  uint16_t swap;
  for (uint8_t carol = 0; carol < num_carols; carol++) {
    swap_with = random(num_carols);  // play_list entry to be swapped out with that in entry '[carol]'
    swap = play_list[carol];
    play_list[carol] = play_list[swap_with];
    play_list[swap_with] = swap;
  }
}

//
// Function waits for the given time in seconds, or part thereof.
//
void wait(float duration) {
  uint32_t start;
  start = millis();
  duration = duration * 1000; // convert to milliseconds
  do {
  } while (millis() - start <= duration);
}

//
// Set tempo by adjusting durations of note/rest timings
//
void set_tempo(float new_tempo) {
  float crotchet_duration;
  current_tempo = new_tempo;           // keep current tempo up to date in case it needs to be queried
  crotchet_duration = 60 / new_tempo;  // timing in seconds for 1 beat
  semib      = crotchet_duration * 4;  // semibrieve, 4 beats
  dot_minim  = crotchet_duration * 3;  // dotted mimin, 3 beats
  minim      = crotchet_duration * 2;  // minim, 2 beats
  crot       = crotchet_duration;      // crotchet, 1 beat
  quav       = crotchet_duration / 2;  // quaver, 1/2 beat
  semiq      = crotchet_duration / 4;  // semiquaver, 1/4 beat
  demi_semiq = crotchet_duration / 8;  // demi-semi-quaver, 1/8 beat
}

//
// Play given note for given duration in seconds, or part thereof.
// Observe that this function is 'blocking', although the tone
// function is 'non-blocking', ie control stays with the function
// until note has completed.
//
void play(int note, float note_duration) {
  tone(speaker, note, note_duration * 1000); // play the given note for the given duration
  wait(note_duration);                       // wait for note to complete
}

//
// Rest for given duration in seconds, or part thereof.
//
void rest(float rest_duration) {
  noTone(speaker);      // ensure no tone is currently playing
  wait(rest_duration);  // wait for given rest to complete
}

void setup() {
  // Set up speaker
  pinMode(speaker, OUTPUT);
  // Set up note/rest timings, based on the default unit beat time (default_tempo)
  set_tempo(default_tempo);
  // Seed random function for shuffling the play_list
  randomSeed(analogRead(A0) + analogRead(A5) + random(1024));
  shuffle_play_list(); // start with a randonmised play_list
}

void loop() {
  do {
    // Process the play_list by selecting each of its preset and randomsised
    // elements, and execute each respective music score funcion.
    for (uint8_t carol = 0; carol < num_carols; carol++) {
      play_list[carol]();  // execute this ([carol]) music score function
      wait(3); // wait a short time between carols
    }
    shuffle_play_list(); // randomise the play_list for the next play_list pass
  } while (true);
}

//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// % Out-of-the-box 'shrink-wrapped' Christmas Carol music scores %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//

void we_wish_you_a_merry_christmas() {
  set_tempo(default_tempo);
  // 3/4time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // intro bar
    play(D4, crot);
    // bar 1
    play(G4, crot);
    play(G4, quav);
    play(A4, quav);
    play(G4, quav);
    play(FS4, quav);
    // bar 2
    play(E4, crot);
    play(E4, crot);
    play(E4, crot);
    // bar 3
    play(A4, crot);
    play(A4, quav);
    play(B4, quav);
    play(A4, quav);
    play(G4, quav);
    // bar 4
    play(FS4, crot);
    play(D4, crot);
    play(D4, crot);
    // bar 5
    play(B4, crot);
    play(B4, quav);
    play(C5, quav);
    play(B4, quav);
    play(A4, quav);
    // bar 6
    play(G4, crot);
    play(E4, crot);
    play(D4, quav);
    play(D4, quav);
    // bar 7
    play(E4, crot);
    play(A4, crot);
    play(FS4, crot);
    // bar 8
    play(G4, minim);
    play(D4, crot);
    // bar 9
    play(G4, crot);
    play(G4, crot);
    play(G4, crot);
    // bar 10
    play(FS4, minim);
    play(FS4, crot);
    // bar 11
    play(G4, crot);
    play(FS4, crot);
    play(E4, crot);
    // bar 12
    play(D4, minim);
    play(A4, crot);
    // bar 13
    play(B4, crot);
    play(A4, crot);
    play(G4, crot);
    // bar 14
    play(D5, crot);
    play(D4, crot);
    play(D4, quav);
    play(D4, quav);
    // bar 15
    play(E4, crot);
    play(A4, crot);
    play(FS4, crot);
    // bar 16
    play(G4, minim);
    rest(crot);
  }
}

void o_come_all_ye_faithful() {
  set_tempo(default_tempo);
  // 4/4 time
  // intro bar
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    play(G4, crot);
    // bar 1
    play(G4, minim);
    play(D4, crot);
    play(G4, crot);
    // bar 2
    play(A4, minim);
    play(D4, minim);
    // bar 3
    play(B4, crot);
    play(A4, crot);
    play(B4, crot);
    play(C5, crot);
    // bar 4
    play(B4, minim);
    play(A4, crot);
    play(G4, crot);
    // bar 5
    play(G4, minim);
    play(FS4, crot);
    play(E4, crot);
    // bar 6
    play(FS4, crot);
    play(G4, crot);
    play(A4, crot);
    play(B4, crot);
    // bar 7
    play(FS4, minim);
    play(E4, crot + quav);
    play(D4, quav);
    // bar 8
    play(D4, dot_minim);
    rest(crot);
    // bar 9
    play(D5, minim);
    play(C5, crot);
    play(B4, crot);
    // bar 10
    play(C5, minim);
    play(B4, minim);
    //  bar 11
    play(A4, crot);
    play(B4, crot);
    play(G4, crot);
    play(A4, crot);
    // bar 12
    play(FS4, crot + quav);
    play(E4, quav);
    play(D4, crot);
    play(G4, crot);
    // bar 13
    play(G4, crot);
    play(FS4, crot);
    play(G4, crot);
    play(A4, crot);
    // bar 15
    play(G4, minim);
    play(D4, crot);
    play(B4, crot);
    // bar 16
    play(B4, crot);
    play(A4, crot);
    play(B4, crot);
    play(C5, crot);
    // bar 17
    play(B4, minim);
    play(A4, crot);
    play(B4, crot);
    // bar 18
    play(C5, crot);
    play(B4, crot);
    play(A4, crot);
    play(G4, crot);
    // bar 19
    play(FS4, minim);
    play(G4, crot);
    play(C5, crot);
    // bar 20
    play(B4, minim);
    play(A4, crot + quav);
    play(G4, quav);
    // bar 21
    play(G4, dot_minim);
    rest(crot);
  }
}

void away_in_a_manger() {
  set_tempo(moderato);
  // 3/4 time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // intro bar
    play(C4, crot);
    // bar 1
    play(F4, crot);
    play(F4, crot);
    play(G4, quav);
    play(A4, quav);
    // bar 2
    play(F4, crot);
    play(F4, crot);
    play(A4, quav);
    play(BF4, quav);
    // bar 3
    play(C5, crot);
    play(C5, crot);
    play(D5, crot);
    // bar 4
    play(BF4, minim);
    play(G4, quav);
    play(A4, quav);
    // bar 5
    play(BF4, crot);
    play(BF4, crot);
    play(C5, crot);
    // bar 6
    play(A4, crot);
    play(A4, crot);
    play(F4, quav);
    play(A4, quav);
    // bar 7
    play(G4, crot);
    play(D4, crot);
    play(F4, crot);
    // bar 8
    play(E4, minim);
    play(C4, crot);
    // bar 9
    play(F4, crot);
    play(F4, crot);
    play(G4, quav);
    play(A4, quav);
    // bar 10
    play(F4, crot);
    play(F4, crot);
    play(A4, quav);
    play(BF4, quav);
    // bar 11
    play(C5, crot);
    play(C5, crot);
    play(D5, crot);
    // bar 12
    play(BF4, minim);
    play(G4, quav);
    play(A4, quav);
    // bar 13
    play(BF4, crot);
    play(BF4, crot);
    play(C5, crot);
    // bar 14
    play(A4, crot);
    play(A4, crot);
    play(F4, quav);
    play(A4, quav);
    // bar 15
    play(G4, crot);
    play(D4, crot);
    play(E4, crot);
    // bar 16
    play(F4, minim);
    rest(crot);
  }
}

void ding_dong_merrily() {
  set_tempo(default_tempo);
  // 4/4 time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // bar 1
    play(G4, crot);
    play(G4, crot);
    play(A4, quav);
    play(G4, quav);
    play(FS4, quav);
    play(E4, quav);
    // bar 2
    play(D4, minim);
    rest(crot);
    play(D4, crot);
    // bar 3
    play(E4, crot);
    play(G4, crot);
    play(G4, crot);
    play(FS4, crot);
    // bar 4
    play(G4, minim);
    play(G4, crot);
    rest(crot);
    // bar 5
    play(G4, crot);
    play(G4, crot);
    play(A4, quav);
    play(G4, quav);
    play(FS4, quav);
    play(E4, quav);
    // bar 6
    play(D4, minim);
    rest(crot);
    play(D4, crot);
    // bar 7
    play(E4, crot);
    play(G4, crot);
    play(G4, crot);
    play(FS4, crot);
    // bar 8
    play(G4, minim);
    play(G4, crot);
    rest(crot);
    // bar 9
    play(D5, crot + quav);
    play(C5, quav);
    play(B4, quav);
    play(C5, quav);
    play(D5, quav);
    play(B4, quav);
    // bar 10
    play(C5, crot + quav);
    play(B4, quav);
    play(A4, quav);
    play(B4, quav);
    play(C5, quav);
    play(A4, quav);
    // bar 11
    play(B4, crot + quav);
    play(A4, quav);
    play(G4, quav);
    play(A4, quav);
    play(B4, quav);
    play(G4, quav);
    // bar 12
    play(A4, crot + quav);
    play(G4, quav);
    play(FS4, quav);
    play(G4, quav);
    play(A4, quav);
    play(FS4, quav);
    // bar 13
    play(G4, crot + quav);
    play(FS4, quav);
    play(E4, quav);
    play(FS4, quav);
    play(G4, quav);
    play(E4, quav);
    // bar 14
    play(FS4, crot + quav);
    play(E4, quav);
    play(D4, crot);
    play(D4, crot);
    // bar 15
    play(E4, crot);
    play(G4, crot);
    play(G4, crot);
    play(FS4, crot);
    // bar 16
    play(G4, minim);
    play(G4, crot);
    rest(crot);
  }
}

void good_king_wenceslas() {
  set_tempo(vivace);
  // 4/4 time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // intro bar
    rest(minim);
    // bar 1
    play(G4, crot);
    play(G4, crot);
    play(G4, crot);
    play(A4, crot);
    // bar 2
    play(G4, crot);
    play(G4, crot);
    play(D4, minim);
    // bar 3
    play(E4, crot);
    play(D4, crot);
    play(E4, crot);
    play(FS4, crot);
    // bar 4
    play(G4, minim);
    play(G4, minim);
    // bar 5
    play(G4, crot);
    play(G4, crot);
    play(G4, crot);
    play(A4, crot);
    // bar 6
    play(G4, crot);
    play(G4, crot);
    play(D4, minim);
    // bar 7
    play(E4, crot);
    play(D4, crot);
    play(E4, crot);
    play(FS4, crot);
    // bar 8
    play(G4, minim);
    play(G4, minim);
    // bar 9
    play(D5, crot);
    play(C5, crot);
    play(B4, crot);
    play(A4, crot);
    // bar 10
    play(B4, crot);
    play(A4, crot);
    play(G4, minim);
    // bar 11
    play(E4, crot);
    play(D4, crot);
    play(E4, crot);
    play(FS4, crot);
    // bar 12
    play(G4, minim);
    play(G4, minim);
    // bar 13
    play(D4, crot);
    play(D4, crot);
    play(E4, crot);
    play(FS4, crot);
    // bar 14
    play(G4, crot);
    play(G4, crot);
    play(A4, minim);
    // bar 15
    play(D5, crot);
    play(C5, crot);
    play(B4, crot);
    play(A4, crot);
    // bar 16
    play(G4, minim);
    play(C5, minim);
    // bar 17
    play(G4, semib);
  }
}

void the_first_nowell() {
  set_tempo(default_tempo);
  // 3/4 time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // intro bar
    rest(minim);
    play(FS4, quav);
    play(E4, quav);
    // bar 1
    play(D4, crot + quav);
    play(E4, quav);
    play(FS4, quav);
    play(G4, quav);
    // bar 2
    play(A4, minim);
    play(B4, quav);
    play(CS5, quav);
    // bar 3
    play(D5, crot);
    play(CS5, crot);
    play(B4, crot);
    // bar 4
    play(A4, minim);
    play(B4, quav);
    play(CS5, quav);
    // bar 5
    play(D5, crot);
    play(CS5, crot);
    play(B4, crot);
    // bar 6
    play(A4, crot);
    play(B4, crot);
    play(CS5, crot);
    // bar 7
    play(D5, crot);
    play(A4, crot);
    play(G4, crot);
    // bar 8
    play(FS4, minim);
    play(FS4, quav);
    play(E4, quav);
    // bar 9
    play(D4, crot + quav);
    play(E4, quav);
    play(FS4, quav);
    play(G4, quav);
    // bar 10
    play(A4, minim);
    play(B4, quav);
    play(CS5, quav);
    // bar 11
    play(D5, crot);
    play(CS5, crot);
    play(B4, crot);
    // bar 12
    play(A4, minim);
    play(B4, quav);
    play(CS5, quav);
    // bar 13
    play(D5, crot);
    play(CS5, crot);
    play(B4, crot);
    // bar 14
    play(A4, crot);
    play(B4, crot);
    play(CS5, crot);
    // bar 15
    play(D5, crot);
    play(A4, crot);
    play(G4, crot);
    // bar 16
    play(FS4, minim);
    play(FS4, quav);
    play(E4, quav);
    // bar 17
    play(D4, crot + quav);
    play(E4, quav);
    play(FS4, quav);
    play(G4, quav);
    // bar 18
    play(A4, minim);
    play(D5, quav);
    play(CS5, quav);
    // bar 19
    play(B4, minim);
    play(B4, crot);
    // bar 20
    play(A4, dot_minim);
    // bar 21
    play(D5, crot);
    play(CS5, crot);
    play(B4, crot);
    // bar 22
    play(A4, crot);
    play(B4, crot);
    play(CS5, crot);
    // bar 23
    play(D5, crot);
    play(A4, crot);
    play(G4, crot);
    // bar 24
    play(FS4, dot_minim);
  }


}

void the_holly_and_the_ivy() {
  set_tempo(default_tempo);
  // 3/4 time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // intro bar
    rest(minim);
    play(G4, crot);
    // bar 1
    play(G4, quav);
    play(G4, quav);
    play(G4, crot);
    play(E5, crot);
    // bar 2
    play(D5, crot);
    play(B4, crot + quav);
    play(G4, quav);
    // bar 3
    play(G4, quav);
    play(G4, quav);
    play(G4, crot);
    play(E5, crot);
    // bar 4
    play(D5, minim);
    play(D5, quav);
    play(C5, quav);
    // bar 5
    play(B4, quav);
    play(A4, quav);
    play(G4, crot);
    play(B4, quav);
    play(B4, quav);
    // bar 6
    play(E4, quav);
    play(E4, quav);
    play(D4, crot);
    play(G4, quav);
    play(A4, quav);
    // bar 7
    play(B4, quav);
    play(C5, quav);
    play(B4, crot);
    play(A4, quav);
    play(A4, quav);
    // bar 8
    play(G4, minim);
    play(G4, quav);
    play(G4, quav);
    // bar 9
    play(G4, quav);
    play(G4, quav);
    play(G4, crot);
    play(E5, crot);
    // bar 10
    play(D5, crot);
    play(B4, crot);
    play(G4, quav);
    play(G4, quav);
    // bar 11
    play(G4, quav);
    play(G4, quav);
    play(G4, crot);
    play(E5, crot);
    // bar 12
    play(D5, minim);
    play(D5, quav);
    play(C5, quav);
    // bar 13
    play(B4, quav);
    play(A4, quav);
    play(G4, crot);
    play(B4, crot);
    //  bar 14
    play(E4, quav);
    play(E4, quav);
    play(D4, crot);
    play(G4, quav);
    play(A4, quav);
    // bar 15
    play(B4, quav);
    play(C5, quav);
    play(B4, crot);
    play(A4, crot);
    // bar 16
    play(G4, minim);
    rest(crot);
  }
}

void we_three_kings() {
  set_tempo(default_tempo);
  // 3/8 time
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // bar 1
    play(B4, crot);
    play(A4, quav);
    // bar 2
    play(G4, crot);
    play(E4, quav);
    // bar 3
    play(FS4, quav);
    play(G4, quav);
    play(FS4, quav);
    // bar 4
    play(E4, crot + quav);
    // bar 5
    play(B4, crot);
    play(A4, quav);
    // bar 6
    play(G4, crot);
    play(E4, quav);
    // bar 7
    play(FS4, quav);
    play(G4, quav);
    play(FS4, quav);
    // bar 8
    play(E4, crot + quav);
    // bar 9
    play(G4, quav + quav);
    play(G4, quav);
    // bar 10
    play(A4, crot);
    play(A4, quav);
    // bar 11
    play(B4, crot);
    play(B4, quav);
    // bar 12
    play(D5, quav);
    play(C5, quav);
    play(B4, quav);
    // bar 13
    play(A4, quav);
    play(B4, quav);
    play(A4, quav);
    // bar 14
    play(G4, crot);
    play(FS4, quav);
    // bar 15
    play(E4, crot + quav);
    // bar 16
    play(FS4, crot + quav);
    // bar 17
    play(A4, crot + quav);
    // bar 18
    play(G4, crot);
    play(G4, quav);
    // bar 19
    play(G4, crot);
    play(D4, quav);
    // bar 20
    play(G4, crot);
    play(E4, quav);
    // bar 21
    play(G4, crot + quav);
    // bar 22
    play(G4, crot);
    play(G4, quav);
    // bar 23
    play(G4, crot);
    play(D4, quav);
    // bar 24
    play(G4, crot);
    play(E4, quav);
    // bar 25
    play(G4, crot + quav);
    // bar 26
    play(G4, crot);
    play(G4, quav);
    // bar 27
    play(A4, crot);
    play(B4, quav);
    // bar 28
    play(C5, crot);
    play(B4, quav);
    // bar 29
    play(A4, crot);
    play(B4, quav);
    // bar 30
    play(G4, crot);
    play(G4, quav);
    // bar 31
    play(G4, crot);
    play(D4, quav);
    // bar 32
    play(G4, crot);
    play(E4, quav);
    // bar 33
    play(G4, crot + quav);
    // bar 34
    rest(crot + quav);
  }
}

void silent_night() {
  set_tempo(default_tempo);
  // 3/4 time
  // intro bar
  rest(crot);
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // bar 1
    play(G4, crot + quav);
    play(A4, quav);
    play(G4, crot);
    // bar 2
    play(E4, dot_minim);
    // bar 3
    play(G4, crot + quav);
    play(A4, quav);
    play(G4, crot);
    // bar 4
    play(E4, dot_minim);
    // bar 5
    play(D5, minim);
    play(D5, crot);
    // bar 6
    play(B4, dot_minim);
    // bar 7
    play(C5, minim);
    play(C5, crot);
    // bar 8
    play(G4, dot_minim);
    // bars 9-12 and 13-16 are identical so repeat twice
    for (uint8_t pass = 1; pass <= 2; pass++) {
      // bar 9, bar 13
      play(A4, minim);
      play(A4, crot);
      // bar 10, bar 14
      play(C5, crot + quav);
      play(B4, quav);
      play(A4, crot);
      // bar 11, bar 15
      play(G4, crot + quav);
      play(A4, quav);
      play(G4, crot);
      // bar 12, bar 16
      play(E4, dot_minim);
    }
    // bar 17
    play(D5, minim);
    play(D5, crot);
    // bar 18
    play(F5, crot + quav);
    play(D5, quav);
    play(B4, crot);
    // bar 19
    play(C5, dot_minim);
    // bar 20
    play(E5, dot_minim);
    // bar 21
    play(C5, crot);
    play(G4, crot);
    play(E4, crot);
    // bar 22
    play(G4, crot + quav);
    play(F4, quav);
    play(D4, crot);
    // bars 23 & 24
    play(C4, dot_minim + dot_minim);
  }
}

void jingle_bells() {
  set_tempo(default_tempo * 2); // very lively
  // 4/4 time
  // intro bar
  rest(minim);
  for (uint8_t repeat = 1; repeat <= 2; repeat++) {
    // bar 1
    play(B3, crot);
    play(B3, crot);
    play(B3, minim);
    // bar 2
    play(B3, crot);
    play(B3, crot);
    play(B3, minim);
    // bar 3
    play(B3, crot);
    play(D4, crot);
    play(G3, crot);
    play(A3, crot);
    // bar 4
    play(B3, semib);
    // bar 5
    play(C4, crot);
    play(C4, crot);
    play(C4, crot);
    play(C4, crot);
    // bar 6
    play(C4, crot);
    play(B3, crot);
    play(B3, crot);
    play(B3, crot);
    // bar 7
    play(B3, crot);
    play(A3, crot);
    play(A3, crot);
    play(B3, crot);
    // bar 8
    play(A3, minim);
    play(D4, minim);
    // bar 9
    play(B3, crot);
    play(B3, crot);
    play(B3, minim);
    // bar 10
    play(B3, crot);
    play(B3, crot);
    play(B3, minim);
    // bar 11
    play(B3, crot);
    play(D4, crot);
    play(G3, crot);
    play(A3, crot);
    // bar 12
    play(B3, semib);
    // bar 13
    play(C4, crot);
    play(C4, crot);
    play(C4, crot);
    play(C4, crot);
    // bar 14
    play(C4, crot);
    play(B3, crot);
    play(B3, crot);
    play(B3, crot);
    // bar 15
    play(D4, crot);
    play(D4, crot);
    play(C4, crot);
    play(A3, crot);
    // bar 16
    play(G3, semib);
  }
}
