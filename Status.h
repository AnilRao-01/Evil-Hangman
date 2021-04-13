#ifndef STATUS_H

#define STATUS_H



enum status { FAILURE, SUCCESS };

typedef enum status Status;



enum boolean { FALSE, TRUE };

typedef enum boolean Boolean;

enum message {Right, Wrong, already_guessed, Blank};

typedef enum message Message;


#endif
