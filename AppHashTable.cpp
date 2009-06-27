/*
 * Copyright 2009, Ilio Catallo, Stefano Celentano, Eleonora Ciceri, all rights reserved
 * Distribuited under the terms of the GPL v2 license
 * 
 * Authors:
 *
 *			Ilio Catallo
 *			Eleonora Ciceri
 * 
 * Last revision: Eleonora Ciceri, 27th June 2009
 *
 * Description: TODO
 */

// Libraries
#include "AppHashTable.h"

#include <stdlib.h>
#include <stdio.h>

// Constructors
AppHashTable :: AppHashTable () {
	head = NULL;
	tail = NULL;
}

AppHashTable :: AppHashTable (Hash* myHead) {
	head = myHead;
	tail = myHead;
}

// Setter
void AppHashTable :: AddNote (BString mySignature, BString myPath) {
	// This is the first node we will insert
	if (head == NULL)  {
		Hash *newElement = new Hash();
		newElement -> signature = mySignature;
		newElement -> notes[0] = myPath;
		newElement -> numNotes = 1;
		newElement -> nextHash = NULL;
		// Initializing head and tail
		head = newElement;
		tail = newElement;	// It points to the last element
	
		printf("(APPHASHTABLE) ho inserito %s in %d\n",head->notes[0].String(),head->numNotes);
	
	}
	// It is a generic element in the list
	else {
		// See if this signature is now in the list
		Hash *temp = new Hash();
		int found = 0;
		
		for (temp = head; temp != NULL; temp = temp -> nextHash) {
			if ( (temp->signature).Compare(mySignature) == 0){//if (strcmp(temp -> signature, mySignature) == 0) {
				// Signature found
				found = 1;
				break;
			}				
		}
		
		// We insert the element
		// Signature not found: we insert in the tail
		if (found == 0){
			Hash *newElement = new Hash();
			newElement -> signature = mySignature;
			newElement -> notes[0] = myPath;
			newElement -> numNotes = 1;
			newElement -> nextHash = NULL;
			// The tail is pushed to the next element	
			tail -> nextHash = newElement;
			tail = tail -> nextHash;	
		}
		// Signature found: we add there
		else {
			int position = temp -> numNotes;
			
			printf("(APPHASHTABLE) ho inserito %s in %d\n",myPath.String(),position);
			
			temp -> notes[position] = myPath;
			temp -> numNotes ++;
			
		
		}
	}
}

// Remove a note from the structure
void AppHashTable :: DeleteNote (BString signature, BString note) {
	int found = 0,
		i = 0;
	Hash *temp = new Hash();
	
	printf("Mi è arrivata signature '%s' e nota '%s'\n", signature.String(), note.String());
	
	if (head == NULL)
		printf("Guarda che la testa è nulla...\n");
	
	for (temp = head; temp != NULL; temp = temp -> nextHash) {
		printf("Sto analizzando %s\n", (temp -> signature).String());
		if ( (temp -> signature).Compare(signature) == 0)
			break;
	}
	
	int nNotes = temp -> numNotes;
	printf(" - Numero note: %d\n", nNotes);

	if (nNotes == 1){
	
		printf("(APPHASHTABLE) unica nota: %s\n",temp->notes[nNotes-1].String());
		if (temp->notes[nNotes-1].Compare(note.String()) == 0){
				printf(">>(APPHASHTABLE) compare corretto\n");
				temp->numNotes = 0;
				
		}
		
	} else {
			// E' la prima nota
			if ((temp -> notes[0]).Compare(note) != 0)
				// Ricerco il nodo da cancellare
				for (i = 1; i < nNotes && found != 1; i++)
					if ((temp -> notes[i]).Compare(note) == 0) {
						printf ("TROVATA! i = %d\n", i);
						found = i;
						break;
					}
			// Nodo trovato: lo cancello
			for (int j = found; j < nNotes; j++) {
				printf("CANCELLO: %s[j = %d] si sovrappone a %s[j = %d]\n", temp -> notes[j + 1].String(), 
							(j + 1), temp -> notes[j].String(), j);
				temp -> notes[j] = temp -> notes[j + 1];
			}
			temp -> notes [nNotes - 1] = "";
			temp -> numNotes --;
		
	
	} //nNotes == 1
	
	// Non ci sono note rimaste
	if (temp -> numNotes == 0) {
		// Ricerco la signature da cancellare
		printf ("Devo cancellare il nodo\n");
		
		if (!head->nextHash){
		
			 head = NULL;
			 return;
		}
		
		for (temp = head; temp->nextHash && (temp -> nextHash -> signature).Compare(signature) != 0; temp = temp -> nextHash) {}
		temp -> nextHash = temp -> nextHash -> nextHash;
	}
}

// Getter
int AppHashTable :: GetNumSignatures() {
	Hash *temp = new Hash();
	int count = 0;
	
	for (temp = head; temp != NULL; temp = temp -> nextHash)
		count ++;
		
	return count;
}

// Number of notes in that signature
int AppHashTable :: GetNumNotes(BString mySignature) {
	Hash *temp = new Hash();
	int count = 0;
	
	for (temp = head; temp != NULL; temp = temp -> nextHash)
		if ( (temp->signature).Compare(mySignature) == 0){ //if (strcmp(temp -> signature, mySignature) == 0) {
			count = temp -> numNotes;
			break;
		}
	
	return count;
}

// Path of the note selected
char* AppHashTable ::GetNote (BString mySignature, int position) {
	Hash *temp = new Hash();
	BString note = NULL;
	
	for (temp = head; temp != NULL; temp = temp -> nextHash)
		if ((temp->signature).Compare(mySignature) == 0){ //if (strcmp (temp -> signature, mySignature) == 0) {
			note = temp -> notes[position];
			break;
		}
		
	return (char *)note.String();
}

// A single signature, selected from the list
char* AppHashTable :: GetSignature (int position) {
	Hash *temp = new Hash();
	
	temp = head;
	for (int i = 0; i < position; i++)
		temp = temp -> nextHash;
		
	return (char *)(temp -> signature).String();
}

bool AppHashTable :: HasElement(){

		if (head) return 1;
		return 0;
}
