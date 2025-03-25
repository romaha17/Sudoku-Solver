#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// TODO: Remove this macro and all its uses in the code before submitting
//       your solution for review!
#define UNUSED(A) ((void) (A))

/* ************************************************************** *
 *               Functions required by assignment                 *
 * ************************************************************** */

bool is_valid_power_two(unsigned int number) {
    return (number & (number - 1)) == 0;
}

unsigned int number_from_power_two(char power) {
    if (power >= '1' && power <= '9') {
        return (1 << (power - '1'));
    }
    if (power == '.' || power == '0') {
        return 0x1ff;
    }
    return 0;
}


bool are_numbers_unique(int array[], int size){
    bool seen[10] = {false};
    for(int i = 0; i < size; i++){
        if(seen[array[i]] && array[i] != 0) {
            return false;
        }else{
            seen[array[i]] = true;
        }
    }
    return true;
}

int power_two(unsigned int number){
    int power = 0;
    while (number > 0) {
        power++;
        number >>= 1;
    }
    return power;
}


bool check_row(unsigned int sudoku[9][9], int num_row){
    int array[9] = {0};
    for (int j = 0; j < 9; j++) {
        if(is_valid_power_two(sudoku[num_row][j])) {
            array[j] = power_two(sudoku[num_row][j]);
        }else{
            continue;
        }
    }
    return are_numbers_unique(array, 9);
}

bool check_column(unsigned int sudoku[9][9], int num_column){
    int array[9] = {0};
    for (int i = 0; i < 9; i++) {
        if(is_valid_power_two(sudoku[i][num_column])) {
            array[i] = power_two(sudoku[i][num_column]);
        }else{
            continue;
        }
    }
    return are_numbers_unique(array, 9);
}

bool check_square(unsigned int sudoku[9][9], int num_of_square){
    int array[9] = {0};
    int rowStart = (num_of_square / 3) * 3;
    int colStart = (num_of_square % 3) * 3;
    int k = 0;
    for(int i = rowStart; i < rowStart + 3; i++){
        for(int j = colStart; j < colStart + 3; j++){
            if(is_valid_power_two(sudoku[i][j])) {
                array[k++] = power_two(sudoku[i][j]);
            }else{
                continue;
            }
        }
    }
    return are_numbers_unique(array, 9);
}

bool check_all_rows(unsigned int sudoku[9][9]){
    for (int i = 0; i < 9; i++) {
        if (!check_row(sudoku, i)) {
            return false;
        }
    }
    return true;
}

bool check_all_columns(unsigned int sudoku[9][9]){
    for (int i = 0; i < 9; i++) {
        if (!check_column(sudoku, i)) {
            return false;
        }
    }
    return true;
}

bool check_all_squares(unsigned int sudoku[9][9]){
    for (int i = 0; i < 9; i++) {
        if (!check_square(sudoku, i)) {
            return false;
        }
    }
    return true;
}


bool eliminate_row(unsigned int sudoku[9][9], int row_index) {
    bool changes = false;
    for (int i = 0; i < 9; i++) {
        if (is_valid_power_two(sudoku[row_index][i])){
            for (int j = 0; j < 9; j++) {
                if (j != i) {
                    if (sudoku[row_index][j] != (sudoku[row_index][j] & ~sudoku[row_index][i])) {
                        changes = true;
                        sudoku[row_index][j] = (sudoku[row_index][j] & ~sudoku[row_index][i]);
                    }
                }
            }
        }
    }
    return changes;
}

bool eliminate_col(unsigned int sudoku[9][9], int col_index) {
    bool changes = false;
    for (int i = 0; i < 9; i++) {
        if (is_valid_power_two(sudoku[i][col_index])) {
            for (int j = 0; j < 9; j++) {
                if (j != i) {
                    if (sudoku[j][col_index] != (sudoku[j][col_index] & ~sudoku[i][col_index])) {
                        changes = true;
                        sudoku[j][col_index] = (sudoku[j][col_index] & ~sudoku[i][col_index]);
                    }
                }
            }
        }
    }
    return changes;
}

bool eliminate_box(unsigned int sudoku[9][9], int row_index, int col_index) {
    bool changes = false;
    int boxStartRow = (row_index / 3) * 3;
    int boxStartCol = (col_index / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (is_valid_power_two(sudoku[boxStartRow + i][boxStartCol + j])) {
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (k != i || l != j) {
                            if (sudoku[boxStartRow + k][boxStartCol + l] != (sudoku[boxStartRow + k][boxStartCol + l] &
                                                                             ~sudoku[boxStartRow + i][boxStartCol +
                                                                                                      j])) {
                                changes = true;
                                sudoku[boxStartRow + k][boxStartCol + l] = (sudoku[boxStartRow + k][boxStartCol + l] &
                                                                            ~sudoku[boxStartRow + i][boxStartCol + j]);
                            }
                        }
                    }
                }
            }
        }
    }
    return changes;
}



char from_int_to_char(unsigned int number){
    if(number == 0){
        return '!';
    }else if(number == 0x1ff){
        return '.';
    }else if(is_valid_power_two(number)){
        return (char)power_two(number) + '0';
    }else{
        return '.';
    }
}

bool needs_solving(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(!is_valid_power_two(sudoku[i][j])){
                return true;
            }
        }
    }
    return false;
}

bool read_border_line(char line[83]){
    int c, i = 0, length = 0;
    while((c = getchar()) != EOF){
        if(c == '\n'){
            line[i] = (char)c;
            length++;
            line[i+1] = '\0';
            break;
        }else{
            line[i] = (char)c;
            i++;
            length++;
        }
    }
    if(length != 26 && length != 82){
        return false;
    }else{
        return true;
    }
}

bool read_number_line(char line[27]){
    int c;
    int length = 0;
    int i = 0;
    while ((c = getchar()) != EOF){
        if(c == '\n'){
            line[i] = (char) c;
            length++;
            line[i+1] = '\0';
            break;
        }else{
            line[i] = (char)c;
            i++;
            length++;
        }
    }
    if(length != 26){
        return false;
    }
    for(i = 0; i < 25; i++){
        if(i % 2 == 1){
            if(line[i] != ' '){
                return false;
            }
        }else if(i % 8 == 0){
            if(line[i] != '|'){
                return false;
            }
        }else{
            if((line[i] < '0' || line[i] > '9') && line[i] != '.'){
                return false;
            }
        }
    }
    return true;
}


void make_line_zero(char line[27]){
    for (int i = 0; i < 25; i++) {
        line[i] = 0;
    }
    line[26] = '\0';
}


bool load_simple(unsigned int sudoku[9][9], char line[83]) {
    int row = 0, column = 0;
    for(int i = 0; i < 81; i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            sudoku[row][column] = number_from_power_two(line[i]);
            column++;
            if (column == 9) {
                row++;
                column = 0;
            }
        }else{
            return false;
        }
    }
    if(line[81] != '\n'){
        return false;
    }else{
        return true;
    }
}

bool load_sudoku_complex(unsigned int sudoku[9][9]) {
    char elements[83] = {0};
    const char border_line[27] = "+=======+=======+=======+\n";
    int row = 0, column = 0;
    for (int section = 0; section < 3; section++) {
        for (int i = 0; i < 3; i++) {
            if (read_number_line(elements)) {
                for (int j = 2; j < 25; j += 2) {
                    if ((j % 2 == 0) && (j % 8 != 0)) {
                        sudoku[row][column] = number_from_power_two(elements[j]);
                        column++;
                        if (column == 9) {  // Check this after you've used the last column.
                            row++;
                            column = 0;
                        }
                    }
                }
            } else {
                return false;
            }
            make_line_zero(elements);
        }
        read_border_line(elements);
        if (strcmp(elements, border_line) == 0) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}


bool is_valid(unsigned int sudoku[9][9])
{
    if(check_all_rows(sudoku) && check_all_columns(sudoku) && check_all_squares(sudoku)){
        return true;
    }
    return false;
}


bool solve(unsigned int sudoku[9][9]) {
    bool changes = true;
    while (changes){
        changes = false;
        for (int i = 0; i < 9; i++) {
            if (eliminate_row(sudoku,i)) {
                changes = true;
            }
        }
        for (int i = 0; i < 9; i++) {
            if(eliminate_col(sudoku,i)){
                changes = true;
            }
        }
        for (int i = 0; i < 9; i+=3) {
            for (int j = 0; j < 9; j+=3) {
                if(eliminate_box(sudoku,i,j)){
                    changes = true;
                }
            }
        }
    }
    return (!needs_solving(sudoku));
}


bool load(unsigned int sudoku[9][9])
{
    char line[83];
    const char border_line[27] = "+=======+=======+=======+\n";
    read_border_line(line);
    if(strlen(line) == 26){
        if(strcmp(line,border_line) == 0){
            if(load_sudoku_complex(sudoku)){
                return true;
            }else{
                return false;
            }
        }
    }else if(strlen(line) == 82){
        if(load_simple(sudoku, line)){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
    return false;
}


void print(unsigned int sudoku[9][9])
{
    for (int i = 0; i < 9; i++) {
        if(i == 0 || i == 3 || i == 6){
            printf("+=======+=======+=======+\n");
        }
        for (int j = 0; j < 9; j++) {
            if(j == 0 || j == 3 || j == 6){
                printf("| %c ", from_int_to_char(sudoku[i][j]));
            }else if(j == 8){
                printf("%c |\n", from_int_to_char(sudoku[i][j]));
            }else{
                printf("%c ", from_int_to_char(sudoku[i][j]));
            }
        }
    }
    printf("+=======+=======+=======+\n");
}

/* ************************************************************** *
 *                              Bonus                             *
 * ************************************************************** */

#ifdef BONUS_GENERATE
void generate(unsigned int sudoku[9][9])
{
    return; // todo
}
#endif

#ifdef BONUS_GENERIC_SOLVE
bool generic_solve(unsigned int sudoku[9][9])
{
    return false; // todo
}
#endif

/* ************************************************************** *
 *                 Adwised auxiliary functionns                   *
 * ************************************************************** */

/* TODO: comment-out #if 0 and correspoding endif to implement */

#if 0
/**
 * @brief Compute the bitset of all done numbers in the box.
 *
 * You might like a similar function for row and for column.
 *
 * @param sudoku 2D array of digit bitsets
 * @param row_index of the top most row in box, one of 0, 3, 6
 * @param col_index of the left most column in box, one of 0, 3, 6
 */
static int box_bitset(unsigned int sudoku[9][9], int row_index, int col_index) {
    return 0;
}

/**
 * @brief Add number into bit set
 *
 * This function encapsulates a bit ands, ors and whatever
 * other bint operations, that would flood the toplevel code
 * with implementation details.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param number    to be added to the set
 *
 * @return          new value of the cell with the number included
 */
static unsigned int bitset_add(unsigned int original, int number) {
    return 0;
}

/**
 * @brief  Drop number from bit set.
 *
 * For detailed description, see bitset_add.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param number    to be dropped from the set
 *
 * @return          new value of the cell without the number included
 */
static unsigned int bitset_drop(unsigned int original, int number) {
    return 0;
}

/**
 * @brief  Check whether given number is present in the set.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param query     number which should be checked for presence
 *
 * @return          true if set, false otherwise
 */
static bool bitset_is_set(unsigned int original, int query) {
	return false;
}

/**
 * @brief  Check whether given cell has a unique value assigned.
 *
 * @param original  bitset to check for single vs. multiple values.
 *
 * @return          true if set, false otherwise
 */
static bool bitset_is_unique(unsigned int original) {
	return false;
}

/**
 * @brief Return next number present in bit set.
 *
 * This function encapsulates a bit ands, ors and whatever
 * other bint operations, that would flood the toplevel code
 * with implementation details.
 *
 * @param original  contents of the 2D sudoku cell.
 * @param previous  last known number present, 0 for start
 *
 * @return          * next (higher) number than argument if such
                    such is present.
 *                  * -1 otherwise
 *
 * @note The value previous might not be in the bitset
 */
static int bitset_next(unsigned int bitset, int previous) {
    return 0;
}

#endif // if 0
