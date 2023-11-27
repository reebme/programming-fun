#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

int main(){
   
    // the # of players
    char *input_line = get_line();
    int n = read_int(input_line); 
    free(input_line);
    // players' scores
    input_line = get_line();
    int *high_scores = (int *)malloc(n * sizeof(int));
    read_n_ints(n, input_line, high_scores);
    free(input_line);
    // # of games
    input_line = get_line();
    int no_games = read_int(input_line);
    free(input_line);
    // scores
    input_line = get_line();
    int *game_scores = (int *)malloc(no_games * sizeof(int));
    read_n_ints(no_games, input_line, game_scores);
    free(input_line);

    printf("No of players: %d\n", n);
    print_array(n, (int *)high_scores);
    printf("No of games: %d\n", no_games);
    print_array(no_games, game_scores);

    exit(EXIT_SUCCESS);
}
