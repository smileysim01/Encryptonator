#include "enigma.h"
#include <stdio.h>
#include <stdlib.h>

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

//For fetching the position of a character in ROTOR_CONSTANTS[0] array
int getPos(char ch, const char *rot){
	int pos;
	for(pos = 0; rot[pos] != '\0'; pos++){
		if(rot[pos] == ch)
			break;
	}
	return pos;
}

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
	char ch;
	int i;
	for(i = 0; (ch = getchar()) != '\n'; i++)
		msg[i] = ch;
	msg[i] = '\0';
    	return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
	char ch;
	int i;
	for(i = 0; ((ch = getchar()) != '\n') && (i < 4); i++){
		which_rotors[i] = ch;
	}
	which_rotors[i] = '\0';
    	return atoi(which_rotors);
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
	int i;
	scanf("%i", &i);
    	return i;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){
	int i, j;
	int len = strlen(which_rotors);
	for(i = 0; i < len; i++){
		for(j = 0; j < 27; j++)
			encryption_rotors[i][j] = ROTOR_CONSTANTS[which_rotors[i] - 48][j];
	}
    	return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
	int i, j, k;
	//int len = sizeof(encryption_rotors)/sizeof(encryption_rotors[0]);
	char last;
	for(i = 0; encryption_rotors[i][0] != '\0'; i++){
		//rotating array one by one to right until rotations
		for(k = 0; k < rotations; k++){
			last = encryption_rotors[i][25];	//stores last element of array
			for(j = 25; j >0; j--)
				encryption_rotors[i][j] = encryption_rotors[i][j-1];	//shifts element to right one by one
			encryption_rotors[i][0] = last;		//adds last element to first position
		}

	}
	
	return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
	int i, j, pos;
	char ch;
	//finding number of rotors used
	int counter = num_active_rotors;
	int len = 0;
	while(counter > 0){
		counter /= 10;
		len++;
	}
	for(i = 0; msg[i] != '\0'; i++){
		if(msg[i] == ' '){
			encrypted_msg[i] = ' ';
			continue;
		}
		pos = getPos(msg[i], ROTOR_CONSTANTS[0]);
		for(j = 0; j < len; j++){
			ch = encryption_rotors[j][pos];
			pos = getPos(ch, ROTOR_CONSTANTS[0]);
		}
		encrypted_msg[i] = ch;
	}
	encrypted_msg[i] = '\0';
	printf("Final = %s\n", encrypted_msg);
	return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
	int i, j, pos;
        char ch;
        //finding number of rotors used
        int counter = num_active_rotors;
        int len = 0;
        while(counter > 0){
                counter /= 10;
                len++;
        }
	decrypted_msg[strlen(encrypted_msg)] = '\0';
	for(i = strlen(encrypted_msg) - 1; i > -1; i--){
		if(encrypted_msg[i] == ' '){
                        decrypted_msg[i] = ' ';
                        continue;
                }
                pos = getPos(encrypted_msg[i], encryption_rotors[len-1]);
                for(j = len-2; j >-1; j--){
			ch = ROTOR_CONSTANTS[0][pos];
                        pos = getPos(ch, encryption_rotors[j]);
                }
                decrypted_msg[i] = ROTOR_CONSTANTS[0][pos];
        }
    	return;
}


