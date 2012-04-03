#include "renju.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *drawing_area;
GtkWidget *label;
extern int array[NUM][NUM];
int winflag=0;

char talk1[4][MAXSIZE] = {"The blind cat turns to the dead rat, you won.", \
							"Actually lost, lost my reputation!", \
							"You win, do not get too excited.", \
							"I lost, and must admit that you are worse than me!"};
char talk2[4][MAXSIZE] = {"Lose it, deserve it!Huh, huh.", \
							"I won. Yes, I'm the one in a peerless master!", \
							"I am a winner. La la la, do not ask who I am.", \
							"You lose. Restrain their grief!"};
char talk3[20][MAXSIZE] = {"Frankly, I prefer to play chess with beautiful.", \
							"I guess you are a master of the world outside.", \
							"How much you have? Rest assured, I asked the age!", \
							"Do you think, how I play chess like?", \
							"This step seems to be the smelly chess?", \
							"It appears to me to surpass.", \
							"You chess nice.", \
							"You are actually one step ahead.", \
							"How many brothers and sisters do you have?", \
							"May I chat with you? ", \
							"It is said that beauty is frosty.", \
							"You look nice.", \
							"You seem to be lost!", \
							"The weather is good today,isn't it?", \
							"I love Europe and America.", \
							"Do you like China? ", \
							"In fact, I'm Chinese.", \
							"I hate Communist Party of China.", \
							"Body, I need a girl.", \
							"Do you know I like Michael Jackson?"};

gint area_redraw(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	int i, j;
	GdkColor     color;
	GdkDrawable	 *canvas;
	GdkGC	       *gc;
	canvas = widget->window;
	gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];

	/* Draw background */	
	color.red = 65535;
	color.green = 47545;
	color.blue = 2855;
	gdk_gc_set_rgb_fg_color (gc, &color);
	for(i=0;i<DRAWING_AREA_WIDTH;i++)
		gdk_draw_line (canvas, gc, 0, i, DRAWING_AREA_WIDTH, i);

	/* Draw lines */
	color.red = 25723;
	color.green = 26985;
	color.blue = 5140;
	gdk_gc_set_rgb_fg_color (gc, &color);
	for(i=0; i<=DRAWING_AREA_WIDTH; i+=SIZE)
		gdk_draw_line (canvas, gc, i, 0, i, DRAWING_AREA_HEIGHT);
	for(i=0; i<=DRAWING_AREA_HEIGHT; i+=SIZE)
		gdk_draw_line (canvas, gc, 0, i, DRAWING_AREA_WIDTH, i);
	
	/* Draw chessman */
	for(i=0; i<NUM; i++)
		for(j=0; j<NUM; j++)
		{
			if(array[i][j]==HUMAN)
			{
				color.red = 65535;
				color.green = 65535;
				color.blue = 65535;
				gdk_gc_set_rgb_fg_color (gc, &color);
				gdk_draw_arc (canvas, gc, TRUE, ROWTOPOS(j), ROWTOPOS(i), CMANSIZE, CMANSIZE, 0, 360*64);
				gdk_draw_arc (canvas, gc, FALSE, ROWTOPOS(j), ROWTOPOS(i), CMANSIZE, CMANSIZE, 0, 360*64);
			}

			if(array[i][j]==COMPUTER)
			{
				color.red = 10000;
				color.green = 10000;
				color.blue = 10000;
				gdk_gc_set_rgb_fg_color (gc, &color);
				gdk_draw_arc (canvas, gc, TRUE, ROWTOPOS(j), ROWTOPOS(i), CMANSIZE, CMANSIZE, 0, 360*64);
				gdk_draw_arc (canvas, gc, FALSE, ROWTOPOS(j), ROWTOPOS(i), CMANSIZE, CMANSIZE, 0, 360*64);
			}
		}
		
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	gdk_gc_set_rgb_fg_color (gc, &color);
	
	return TRUE;
}

gint area_click(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	int x1, y1, x2, y2, ran_num, rtn;
	rtn = 10;
	char words[MAXSIZE+10];
	char msg[MAXSIZE];
	static int count=0;

	x1 = y1 = x2 = y2 = 0;
	GdkModifierType state;
	GtkWidget    *dialog;
	GdkColor     color;
	GdkDrawable	 *canvas;
	GdkGC	       *gc;
	canvas = widget->window;
	gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];

	count++;
	gdk_window_get_pointer(widget->window, &x1, &y1, &state);

	if(winflag==0)
		rtn = play(CURTOROW(x1), CURTOROW(y1), &x2, &y2);


		if(rtn<0)
	{
		memset(words, 0, sizeof(words));
		snprintf(words,sizeof(words)-1, "[Computer] says: Please restart the game.");
		gtk_label_set_text(label, words);
		
		/* show dialog */
		memset(msg, 0, sizeof(msg));
		snprintf(msg, sizeof(msg)-1, "Might have been a draw?!");
		dialog=gtk_message_dialog_new(GTK_WINDOW(window),0,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	
	if(winflag==0 &&rtn==0)
	{
		color.red = 65535;
		color.green = 65535;
		color.blue = 65535;
		gdk_gc_set_rgb_fg_color (gc, &color);
		gdk_draw_arc (canvas, gc, TRUE, CURTOPOS(x1), CURTOPOS(y1), CMANSIZE, CMANSIZE, 0, 360*64);
		gdk_draw_arc (canvas, gc, FALSE, CURTOPOS(x1), CURTOPOS(y1), CMANSIZE, CMANSIZE, 0, 360*64);
		
		color.red = 10000;
		color.green = 10000;
		color.blue = 10000;
		gdk_gc_set_rgb_fg_color (gc, &color);
		gdk_draw_arc (canvas, gc, TRUE, ROWTOPOS(x2), ROWTOPOS(y2), CMANSIZE, CMANSIZE, 0, 360*64);
		gdk_draw_arc (canvas, gc, FALSE, ROWTOPOS(x2), ROWTOPOS(y2), CMANSIZE, CMANSIZE, 0, 360*64);
		
		srand((unsigned)time(0)+count);
		ran_num = rand()%20;
		memset(words, 0, sizeof(words));
		snprintf(words,sizeof(words)-1, "[Computer] says: %s", talk3[ran_num]);
		gtk_label_set_text(label, words);
	}
	
	if(winflag==0 &&rtn==HUMAN)
	{
		winflag = 1;
		srand((unsigned)time(0)+count);
		ran_num = rand()%4;
		memset(words, 0, sizeof(words));
		snprintf(words, sizeof(words)-1, "[Computer] says: %s", talk1[ran_num]);
		gtk_label_set_text(label, words);
		
		/* show dialog */
		memset(msg, 0, sizeof(msg));
		snprintf(msg, sizeof(msg)-1, "[Human] is winner.\nall [%d] steps", count);
		dialog=gtk_message_dialog_new(GTK_WINDOW(window),0,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	
	if(winflag==0 &&rtn==COMPUTER)
	{
		winflag = 1;
		srand((unsigned)time(0)+count);
		ran_num = rand()%4;
		memset(words, 0, sizeof(words));
		snprintf(words,sizeof(words)-1, "[Computer] says: %s", talk2[ran_num]);
		gtk_label_set_text(label, words);
		
		/* show dialog */
		memset(msg, 0, sizeof(msg));
		snprintf(msg, sizeof(msg)-1, "[Computer] is winner.\nall [%d] steps", count);
		dialog=gtk_message_dialog_new(GTK_WINDOW(window),0,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	
		if(rtn==3)
	{
		memset(words, 0, sizeof(words));
		snprintf(words,sizeof(words)-1, "[Computer] says: Please obey the rules!");
		gtk_label_set_text(label, words);
		
		/* show dialog */
		memset(msg, 0, sizeof(msg));
		snprintf(msg, sizeof(msg)-1, "Does not comply with the rules of the game!");
		dialog=gtk_message_dialog_new(GTK_WINDOW(window),0,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	return TRUE;
}

int main(int argc, char **argv)
{
	gtk_set_locale();
	gtk_init(&argc, &argv);
	
	/* Create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_usize(window, WINWIDTH, WINHEIGHT);
	gtk_container_set_border_width(GTK_CONTAINER(window), WINDOW_BORDER_WIDTH);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW(window), "Renju");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	g_signal_connect_swapped(G_OBJECT(window),  "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	/* Create a new drawing area */
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawing_area, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT);

	/* Add events */
	g_signal_connect(G_OBJECT(drawing_area), "expose_event", G_CALLBACK(area_redraw), NULL);
	gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK);
	g_signal_connect (GTK_OBJECT(drawing_area), "button_press_event", GTK_SIGNAL_FUNC(area_click), (gpointer) drawing_area);

	/* Create a new text */
	label = gtk_label_new(" ");
	gtk_widget_set_size_request(label, LABELWIDTH, LABELHEIGHT);
	gtk_label_set_line_wrap (label, TRUE);
	
	fixed = gtk_fixed_new();
	gtk_widget_set_usize(fixed,20,20);
	gtk_fixed_put(GTK_FIXED(fixed),label,0,0);
	gtk_fixed_put(GTK_FIXED(fixed),drawing_area,0,LABELHEIGHT+5);
	gtk_container_add(GTK_CONTAINER(window), fixed);
	
	/* Initialize array */
	int i, j;
	for(i=0; i<NUM;i++)
	{
		for(j=0; j<NUM;j++)
			array[i][j] = EMPTY;
	}

	/* show all windows */

	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}
