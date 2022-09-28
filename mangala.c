#include <stdio.h>

int
main()
{
	int board[14];

	int choice;
	int i;

	/* game_init */
	for (i = 0; i < 14; i++)
		board[i] = 4;
	board[6] = 0;
	board[13] = 0;

	do {
		printf("%d --", board[13]);
		for (i = 12; i > 6; i--)
			printf(" %d", board[i]);
		puts("");

		printf("    ");
		for (i = 0; i < 6; i++)
			printf(" %d", board[i]);
		printf(" -- %d\n", board[6]);

		printf("select: ");
		if (scanf("%d", &choice) == EOF) continue;

		if (choice < 0 || choice > 6) {
			puts("please enter a number between 1 and 6");
			puts("or 0 to quit");
		}
	} while (choice != 0);

	return 0;
}
