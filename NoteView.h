#ifndef NOTE_VIEW_H
#define NOTE_VIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _TEXT_VIEW_H
#include <TextView.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _STRING_H
#include <String.h>
#endif



class NoteView : public BTextView {
	public:
						
						NoteView (BRect frame, BRect frameText, char *name,BHandler *handler);
						NoteView (BMessage *msg);
	   				   ~NoteView();
	   	void			Init();
static 	BArchivable*	Instantiate(BMessage *msg);
		void			AboutRequested();	   
	    status_t		Archive(BMessage *msg,bool deep=true) const;
		void			MessageReceived(BMessage *msg);
		
		void 			SetBackgroundColor(rgb_color colore);
virtual	void 			InsertText(const char *text, int32 length, int32 offset, const text_run_array *runs=NULL);

	private:
	
		BHandler 	*handler;
		BMessenger 	*fMessenger;
		BString 	*message;
	

};

#endif