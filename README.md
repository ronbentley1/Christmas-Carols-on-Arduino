# Christmas-Carols-on-Arduino
10 plug and play Christmas carols on Arduino microcontroller with 8 ohm speaker

# In a Nut Shell
'Christmas Carols on Arduino' comprises a single sketch incorporating a play list of 10 popular Christmas carols. The play list of 10 carols is randomised after each complete play cycle and replayed in a new order. The out of the box (OOTB) carols are:

- We Wish You A Merry Christmas
- O Come All Ye Faithful
- Away In A Manger
- Ding Dong Merrily (On High)
- Good King Wenceslas
- The First Nowell
- The Holly And The Ivy
- We Three Kings
- Silent Night
- Jingle Bells

(Each carol function runs through two complete play cycles, but this may be increased, or otherwise, as you wish by making a simple change to the associated carol functions for-loop upper bounds.)

#bThe Christmas Carols on Arduino sketch is 'plug and play', but there are two ways in which you can approach this article/project -

1. you can make the speaker circuit as outlined (see Hardware and Schematics below), download and run the associated sketch as is, sit back with a cup of coffee (or, if it is the festive season, some other libation!) and enjoy some carols,

or

2. you can make the speaker circuit as outlined, download the associated sketch and explore its structure, content and methods (it offers a particularly interesting technique that you may find useful in you own future projects).

If your approach is the first, then great, job done, enjoy the carols and keep the sketch for future use - you do not to read any further. However, if you are the curious type and want to understand how the Christmas carol sketch works then read on.

# The Hardware
Couldn't be simpler - all you will need is an Arduino microcontroller (any should be okay), a 100 ohm resistor, a small bread board, some wires and, preferably, an 8 ohm 0.25 watt speaker (or a buzzer if you don't have a speaker to hand).

The wiring diagram is as shown below at Schematics, but it is a very simple circuit to put together. The sketch uses digital output pin 11 to drive the speaker, but if you wish to use another, then choose a suitable alternative pin and change the definition '#define speaker' in the sketch as required.

I should advise that the microcontroller should not be directly connected to anything but a speaker/buzzer as outlined, otherwise you may damage your microcontroller.

# The Sketch - Points of Note
The sketch is derived of a previous article/publication 'Let's Make Music', modified specifically to manage a play list of musical scores (carols). The sketch design is straight forward and should be easily followed by the interested. It does, however, include a technique that is worthy of particular note - the use of pointers to define and manage the carols play list (C++ pointers).

If you are fully appraised of pointers, their purpose and use then you can skip this part, otherwise, it is worth taking a little time to explore how these are used by the sketch.

Let's start with how the design makes use of pointers:

Firstly, each carol music score is defined by its own function with these functions being placed at the end of the sketch, just to avoid cluttering up the sketch and help readability.
Next, at the top part of the sketch, we define forward references for the each of the carol functions as we will need to assign these to our play list array (which is defined as an array of pointers). This is done prior to the declaration of the play list pointer array as it is necessary to ensure that the address references of the carol functions are in scope at the point at which they are needed by the complier. We could have simply declared the carol functions before we declare the play list pointer array, at the top of the sketch, but that would just add a lot of clutter to the sketch where it is helpful for it to be clutter free.
After the carol function forward references are declared, the sketch then defines a play list (play_list) which is an array of type pointer (*) of size equal to the number of carols (carol functions) declared in the sketch (OOTB this will be of size 10). Each element of the play list array is then assigned (preset) with the address reference of each of the carol functions (this is only possible because of the forward carol function declarations).
Now that has been done we are able to use/process the play list as required - eg shuffle (randomise) it, step through it element by element and invoke the associated carol functions, etc.
To recap, let's look at each bit of code in the sketch that allow us to use a pointer based play list.

Forward Reference Declarations To The Carol Functions - note the syntax:

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

Play List Declaration - we declare the play list pointer array with carol function address presets (again, note the syntax):

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


The syntax to define the play list as an array of pointers looks a little strange, but the two points to note are:

1. the '*' character before the array name. This tells the compiler that the array 'play_list' should be treated as an array of pointers, and
2. the ending '()' characters. Again this alerts the compiler that the address references relate to functions (our forward carol function references). This allows us to then invoke the functions defined by the play list elements directly - see Main Loop, below.
Note also that we are able to preset the play list pointer array only because we have previously declared the forward references to the carol functions. The complier presets each element of the play list array with the address of the declared carol function. The order in which these are preset is not important as the play list is continually randomly shuffled.

That's it. We are now able to process the play list how we please. Let's look at the main loop:

Main Loop - the main loop will be seen to be almost trivial in its design:

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


The main loop simply goes through each play list element calling its associated carol function - once again, note the syntax - we treat the play list as pseudo function, hence the use of the '()' characters in the call.

After each complete play list cycle, the play list is randomly shuffled so that we get a different carol ordering at each next pass.

There are many ways in which pointers can be used and, hopefully, by examining their use in this sketch, you can think about how they can be helpful for your own sketch designs.

Anyway, that's all for this article, for now, and I hope you have found enjoyment in the carols and even, perhaps, added your own carols to the sketch.

# Next Steps?
Why not add your own carols? 
