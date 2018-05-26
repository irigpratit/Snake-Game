#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <SDL/SDL.h>

#define SNAKE_MAX_SIZE 100
#define SNAKE_HEAD 5
#define SNAKE_SPEED 100
#define SCREEN_X 180
#define SCREEN_Y 180
#define xmacro_opposite(x) \
	((x) == SDLK_UP ? SDLK_DOWN : \
	 (x) == SDLK_DOWN ? SDLK_UP : \
	 (x) == SDLK_RIGHT ? SDLK_LEFT : \
	 (x) == SDLK_LEFT ? SDLK_RIGHT : \
	 SDLK_UNKNOWN)
void put_square(SDL_Surface *, SDL_Rect, Uint8);

SDL_Surface* gXOut = NULL;  //The image we will load and show on the screen
SDL_Surface* gXStart = NULL;
SDL_Surface* endUI = NULL;

struct Snake {
	SDL_Rect body[SNAKE_MAX_SIZE];
	SDL_Rect position;
	size_t size;
	size_t startsize;
	Uint8 colour;
	unsigned direction;
};
SDL_Rect newmouse(struct Snake *, SDL_Surface *);
SDL_Rect pop(struct Snake *);
void push(struct Snake *);
size_t len;
int main(int argc, char **argv) {
	int crash =0;
	int previous_score = 0;
	int score = 0;
	SDL_Surface *screen;
	SDL_Event event;
	SDL_Rect mouse;
	struct Snake snake;
	size_t counter;
	unsigned char mousecolours[] =
	{ 10, 40, 50, 67, 182, 133, 242 };
	int walls = 0;
	if(SDL_Init(SDL_INIT_VIDEO) ==  -1) {
	fprintf(stderr, "%s\n", SDL_GetError());
		return -1;
	}
	if(atexit(SDL_Quit) == -1) {
		perror("atexit");
		SDL_Quit();
		return -1;
	}
	screen = SDL_SetVideoMode(800,600, 8, SDL_SWSURFACE);
	if(screen == NULL) {
	fprintf(stderr, "%s\n", SDL_GetError());
		return -1;
	}

	gXOut = SDL_LoadBMP( "start.bmp" );    // display_start_screen

	if( gXOut == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
	}

	SDL_BlitSurface( gXOut, NULL, screen, NULL );
		SDL_Flip(screen);
	SDL_Event e;
		void crashcheck(int crash){
		if (crash == 1){
			endUI = SDL_LoadBMP("end.bmp");
			SDL_BlitSurface( endUI, NULL, screen, NULL );
			SDL_Flip(screen);
			SDL_Delay(5000);

		}
	}	
	while(1) {
		 SDL_PollEvent( &e );
		 SDL_Delay(50);
				if( e.type == SDL_QUIT )   				//User requests quit
					{
						exit(0);
					}

					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                        printf("entered");
						break;
					}
	}

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen -> format, 0, 0, 0));
	if(argc > 1) {
		if(argv[1][0] == '0')
			walls = 0;
		else walls = 1;
	}
	srand(time(NULL));
	SDL_WM_SetCaption("snake game!", NULL);
	memset(screen->pixels, 0, SCREEN_X * SCREEN_Y);
	memset(&snake, 0, sizeof snake);
	snake.colour = 100;
	snake.direction = SDLK_RIGHT;
	snake.startsize = 5;
	for(counter = 0; counter < snake.startsize; counter++)
		push(&snake);
	put_square(screen, snake.position, snake.colour);
	mouse = newmouse(&snake, screen);
	put_square(screen, mouse, mousecolours[rand() % sizeof mousecolours]);
	SDL_Flip(screen);

	for(counter = 0; 1; counter++) {
		if(SDL_PollEvent(&event))
		switch(event.key.keysym.sym) {

			case SDLK_SPACE:
				push(&snake);
				break;

			case SDLK_ESCAPE:
				SDL_FreeSurface(screen);
				return 0;
				break;

			case SDLK_UP:
				if(snake.direction != xmacro_opposite(SDLK_UP))
					snake.direction = SDLK_UP;
				break;
			case SDLK_LEFT:
				if(snake.direction != xmacro_opposite(SDLK_LEFT))
					snake.direction = SDLK_LEFT;
				break;
			case SDLK_DOWN:
				if(snake.direction != xmacro_opposite(SDLK_DOWN))
					snake.direction = SDLK_DOWN;
				break;
			case SDLK_RIGHT:
				if(snake.direction != xmacro_opposite(SDLK_RIGHT))
					snake.direction = SDLK_RIGHT;
				break;
				
			default:
				break;
		}
		
		void scoreCheck(){
			FILE *f = fopen("score.txt", "r");
					if(f != NULL) {
						fscanf(f, "%d", &previous_score);
					}
					score = snake.size - snake.startsize;
					printf("Previous Score: %d, CONGRATULATIONS Your Score is::: %d\n", previous_score, score);
					if (score > previous_score) {

						FILE *f = fopen("score.txt", "a");
						fprintf(f, "%d", score);
						fclose(f);
					}			
		}
				if(snake.direction == SDLK_UP) {
					if(snake.position.y == 0) {
						if(walls == 0) {
						SDL_FreeSurface(screen);
						scoreCheck();
						crash = 1;
						crashcheck(crash);	
				}
				else
					snake.position.y = screen->h;
			}
			snake.position.y -= SNAKE_HEAD;
		}

				if(snake.direction == SDLK_DOWN) {
					if(snake.position.y == screen->h - SNAKE_HEAD) {
						if(walls == 0) {
							SDL_FreeSurface(screen);
							scoreCheck();
							crash = 1;
							crashcheck(crash);
						}
				else
					snake.position.y = -SNAKE_HEAD;
			}
			snake.position.y += SNAKE_HEAD;
			}
		
			if(snake.direction == SDLK_RIGHT) {
				if(snake.position.x == screen->w - SNAKE_HEAD) {
					if(walls == 0) {
						SDL_FreeSurface(screen);
						scoreCheck();
						crash = 1;
						crashcheck(crash);
				}
				else
					snake.position.x = -SNAKE_HEAD;
			}
			snake.position.x += SNAKE_HEAD;
		
			}
		if(snake.direction == SDLK_LEFT) {
			if(snake.position.x == 0) {
				if(walls == 0) {
					SDL_FreeSurface(screen);
					scoreCheck();
					crash = 1;
					crashcheck(crash);
				}
				else
					snake.position.x = screen->w;
			}
			snake.position.x -= SNAKE_HEAD;
		}
			for(counter = 0; counter < snake.size; counter++)
			if(snake.position.x == snake.body[counter].x
					&& snake.position.y == snake.body[counter].y) {
				SDL_FreeSurface(screen);
				scoreCheck();
					crash = 1;
					crashcheck(crash);
			}
		put_square(screen, snake.position, snake.colour);
		if(snake.position.x == mouse.x && snake.position.y == mouse.y) {
			mouse = newmouse(&snake, screen);
			put_square(screen, mouse, mousecolours[rand() % sizeof mousecolours]);
		}
		else
			put_square(screen, pop(&snake), 0);
		push(&snake);
		SDL_Flip(screen);
		SDL_Delay(SNAKE_SPEED);
	}
	SDL_FreeSurface(screen);
	return 0;
}
SDL_Rect newmouse(struct Snake *ptr, SDL_Surface *screen) {
	SDL_Rect ret = { 0, 0, 0, 0};
	size_t n;
	int x, y;
	int ok = 1;
	x = screen->w / SNAKE_HEAD;
	y = screen->h / SNAKE_HEAD;

	while(ok != 0) {
		ok = 0;
		ret.x = (rand() % x) * SNAKE_HEAD;
		for(n = 0; n < ptr->size; n++)
			if(ret.x == ptr->body[n].x) {
				ok = 1;
				break;
			}
		if(ok == 0) {
			ret.y = (rand() % y) * SNAKE_HEAD;
			for(n = 0; n < ptr->size; n++)
				if(ret.y == ptr->body[n].y) {
					ok = 1;
					break;
				}
		}
	}
	return ret;
}

void push(struct Snake *ptr) {
	if(ptr->size != SNAKE_MAX_SIZE) {
		ptr->body[ptr->size] = ptr->position;
		ptr->size++;
	}
}
SDL_Rect pop(struct Snake *ptr) {

	SDL_Rect ret = { 0, 0, 0, 0 };

	if(ptr->size != 0) {
		ret = ptr->body[0];
		if(ptr->size-- > 1)
			memmove(ptr->body, &ptr->body[1], ptr->size * sizeof ptr->body[0]);
	}

	return ret;
}
void put_square(SDL_Surface *screen, SDL_Rect foo, Uint8 color) {
	int i, n;
	Uint8 *p = screen->pixels;
	p += foo.x + foo.y * screen->w;

	for(n = 0; n < SNAKE_HEAD; n++) {
		for(i = 0; i < SNAKE_HEAD; i++)
			*p++ = color;
		p += screen->w - SNAKE_HEAD;
	}
}
