/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

/*
 * Anleitung:
 * 	Standardmodus:
 * 		<Zahl1><operator><Zahl2>
 * 		-> Zahlen als float
 * 		-> operator ist '+', '-', '*', '/' oder '^' (Potenz)
 *
 * 	Erweiterter Modus:
 * 		<Befehl> <Formel>
 * 		-> Befehle:
 * 			- "eval" -> rechnet term aus. Falls der Term variablen enthält, werden diese vom Benutzer eingelesen.
 * 			- "eval_rep" -> rechnet term mit variablen wiederholt aus. Vor jedem durchlauf werden alle Variablen eingelesen.
 * 				Nach jedem Durchlauf wird abgefragt ob die Operation beendet oder wiederholt werden soll.
 * 			- "tree" -> Visualisiert die Binaerbaum-Repraesentation der eingegebenen Formel mit der Wurzel links
 * 		-> Formeln
 * 			-> Formeln können aus beliebig vielen Operatoren <'+'; '-'; '*'; '/', '^'(Potenz)> , Zahlen und Klammern "(" + ")" bestehen.
 * 				Außerdem sind Variablen mit Bezeichnern aus 1 oder mehreren Buchstaben zulaessig.
 * 			-> Operatoren- bzw. Klammer-priorisierung wird intern gehandhabt (Klammern > Potenz > Punkt > Strich), ansonsten wird von rechts nach links gerechnet
 * 			-> Negative Werte bzw. Variablen sollten in Klammern gesetzt werden; z.B. "eval 5*(-2) + (-b)*b"
 * 			-> Variabelnamen beginnen mit einem Buchstaben, koennen aber auch Zehlen enthalten
 * 			-> Beispiele:
 * 				"eval 1+2+3+4+5"
 * 				"eval 1+2*3+4*5"
 * 				"eval 2*3^2" -> 18
 * 				"eval (2*3)^2" -> 36
 * 				"eval a*a + 2*a*b + b*b"
 * 				"eval var1 * 4 + var2"
 * 				"eval_rep a*b+g-h/j"
 * 				"tree 3*a*a + 2*a - 7"
 * 				"tree var1*b-b2*r2-r1*r1"
 * 
 * 	#########################################################  WICHTIG:
 * 
 * 		Der optionale teil dieser abgabe kann problemlos deaktiviert bzw. entfernt werden.
 * 			zum Deaktivieren: Zeile 121 und 122 auskommentieren / entfernen.
 * 
 * 			zum vollstaendigen entfernen: zusaetzlich Funktionsprototyp in Zeile 54 und alles ab Zeile 130 entfernen.
 * 
 */


#include <math.h> // Fuer pow()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------   Fuer c Bools:   ------------------------
// typedef enum { false = 0, true = !false } bool;

bool printAdvancedCalc(const char *const input); // Freiwillige erweiterung

void flushInput() {
	for(;;) { int c = getchar(); if(/*c=='\r' || */c=='\n' || c==EOF) break; }
}

float calc(const float val1, const float val2, const char operation) {
	switch(operation) {
		case '+':
			return val1 + val2;

		case '-':
			return val1 - val2;

		case '*':
			return val1 * val2;

		case '/':
			return val1 / val2; // let IEEE-754 handle division by zero

		case '^': // Potenz
			return powf(val1, val2);
	}
	printf("Fehler: mathematische Operation '%c' nicht verstanden.\n", operation);
	return 0. / 0.; // NaN
}

bool printSimpleCalc(const char *const input) { // returns true on success
	char operation;
	float num1, num2;

	if(sscanf(input, "%f%c%f", &num1, &operation, &num2) != 3) // versuchen, den Term aus dem char[] zu extrahieren
		return false;

	// Teilen durch 0 verhindern
	if(operation == '/' && num2 == 0) {
		printf("Fehler: Teilen durch 0 nicht erlaubt\n"); // selbsterklaerend
		return false;
	}

	const float res = calc(num1, num2, operation); // Term ausrechnen

	if(res != res) // calc hat NaN zurueckgegeben (NaN != NaN laut IEEE 754)
		return false;

	printf("%f %c %f = %f\n", num1, operation, num2, res); // gesamte Loesung ausgeben
	return true;
}

int main(int argc, char** argv) { // Aufgabe 1 (Taschenrechner)
	for(;;) {
		printf("\nTaschenrechner:\n");
		char input[256];
		if(fgets(input, 256, stdin) == NULL) { // eingabe bis inklusive \n in <input> einlesen, fgets==0 bedeutet Fehler
			if(feof(stdin)) { // EOF gefunden -> nutzer versucht Programm zu beenden
				printf("EOF registriert, Rechner wird geschlossen!\n");
				return 0;
			}
			printf("Fehler beim Lesen des Inputs, bitte versuchen sie es erneut!\n");
			flushInput();
			continue;
		}

		if(printSimpleCalc(input)) // rest der Schleife ueberspringen falls printSimpleCalc erfolgreich
			continue;


		if(printAdvancedCalc(input)) // -------   Freiwillige Erweiterung, zum deaktivieren entfernen
			continue;                // -------   Freiwillige Erweiterung, zum deaktivieren entfernen


		printf("Fehlerhafter Input, bitte versuchen sie es erneut!\n"); // Wird nur ausgefuehrt, wenn alle interpretationsversuche fehlgeschlagen sind
	}
}






// -----------------------------------   Ab hier Freiwillige Erweiterung (Binaerbaum-basierter Funktionsparser)

/* WARNUNG: Der folgende Code ist in c geschrieben. Längere betrachtung kann u.a. zu
 * Kopfschmerzen, permanenter Sehschädigung u. Depressionen führen. Zu Risiken und Nebenwirkungen fragen
 * sie ihren Arzt oder Apotheker.
 */

typedef enum { EQUATION, CONSTANT, VARIABLE } AST_TYPE;

typedef struct sAST AST;
struct sAST {
	AST_TYPE type;
	union {
		struct {
			AST *before, *after;
			char operation;
		};
		float value;
		char *variableName;
	};
};

void printAST(const AST *const ast, const int indent) {
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			for(int i = 0; i < indent; i++) printf("  ");
			printf("%f\n", ast->value);
			break;

		case AST_TYPE::VARIABLE:
			for(int i = 0; i < indent; i++) printf("  ");
			printf("%s\n", ast->variableName);
			break;

		case AST_TYPE::EQUATION:
			printAST(ast->before, indent + 1);
			for(int i = 0; i < indent; i++) printf("  ");
			printf("%c\n", ast->operation);
			printAST(ast->after, indent + 1);
			break;
	}
}

void printFormula(const AST *const ast) {
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			printf("%f", ast->value);
			break;

		case AST_TYPE::VARIABLE:
			printf("%s", ast->variableName);
			break;

		case AST_TYPE::EQUATION:
			printf("(");
			printFormula(ast->before);
			printf(" %c ", ast->operation);
			printFormula(ast->after);
			printf(")");
			break;
	}
}



#define printf // disable printf's in buildAST
AST * buildAST(const char *const expression, const int numChars) {
	// printf("BuildAST[");
	// for(int i=0; i<numChars; i++)
	// 	if(expression[i] != '\n')
	// 		printf("%c", expression[i]);
	// printf("]");
	printf("<");
	typedef struct sAstCollection AstCollection;
	struct sAstCollection {
		AST *ast;
		AstCollection *next;
	};
	typedef struct sOperation Operation;
	struct sOperation {
		char operation;
		Operation *next;
	};
	AstCollection *astCollection = NULL, **lastAstElement = &astCollection;
	Operation *operations = NULL, **lastOperation = &operations;

	for(int c = 0; c < numChars;) {
		const char current = expression[c];
		switch(current) {
			case '(':
				{
					int openBrackets = 1;
					const char *const substr = expression + c + 1;
					for(int substrLength = 0; ; substrLength++) {
						if(substr[substrLength] == '(')
							openBrackets++;
						if(substr[substrLength] == ')' && --openBrackets==0) {
							if(*lastAstElement == NULL)
								astCollection = (AstCollection*)malloc(sizeof(AstCollection));
							else {
								lastAstElement[0]->next = (AstCollection*)malloc(sizeof(AstCollection));
								lastAstElement = &(lastAstElement[0]->next);
							}
							lastAstElement[0]->ast = buildAST(substr, substrLength);
							lastAstElement[0]->next = NULL;
							c += 1 + substrLength;
							break;
						}
					}
				}
				break;

			case ')':
				printf("Error: Closed more Brackets than opened before\n");
				return NULL;

			case '-':
				if(!astCollection) {
					astCollection = (AstCollection*)malloc(sizeof(AstCollection));
					astCollection->ast = (AST*)malloc(sizeof(AST));
					astCollection->ast->type = AST_TYPE::CONSTANT;
					astCollection->ast->value = 0;
					astCollection->next = NULL;
				}
			case '+':
			case '*':
			case '/':
			case '^':
				if(*lastOperation == NULL) {
					operations = (Operation*)malloc(sizeof(Operation));
				} else {
					lastOperation[0]->next = (Operation*)malloc(sizeof(Operation));
					lastOperation = &(lastOperation[0]->next);
				}
				lastOperation[0]->operation = current;
				lastOperation[0]->next = NULL;
				printf("Operator(%c); ", current);
				break;

			case ' ': // skip irrelevant chars
			case '\r':
			case '\n':
				break;

			default:
				if((current >= '0' && current <= '9') || current == '.') { // digit
					float num = 0;
					bool fractPart = false;
					short fractIndex = 0; // n'th digit after decimal point
					const char *const numStr = expression + c;
					for(int i = 0; ; i++) {
						if(numStr[i] == '.') {
							if(fractPart) {
								printf("Error: found two decimal points in one numeric literal\n");
								return NULL;
							}
							fractPart = true;
							continue;
						}
						if(numStr[i] < '0' || numStr[i] > '9')
							break;
						const char digit = numStr[i] - '0';
						if(!fractPart) {
							num = num * 10 + digit;
						} else {
							float tenToFractIndex = 10;
							for(int j = 0; j < fractIndex; tenToFractIndex *= 10, j++);
							num += digit / tenToFractIndex;
						}
					}

					AST *newAST = (AST*)malloc(sizeof(AST));
					newAST->type = AST_TYPE::CONSTANT;
					newAST->value = num;
					if(*lastAstElement == NULL) {
						astCollection = (AstCollection*)malloc(sizeof(AstCollection));
						lastAstElement = &(astCollection);
					} else {
						lastAstElement[0]->next = (AstCollection*)malloc(sizeof(AstCollection));
						lastAstElement = &(lastAstElement[0]->next);
					}
					lastAstElement[0]->ast = newAST;
					lastAstElement[0]->next = NULL;
					printf("Value(%f); ", num);
					break;
				}
				if((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z')) { // character
					// printf("Error: not handling characters yet\n");
					// return NULL;

					int varNameLength = 0;
					char variableName[128]{0};
					for(; ; varNameLength++) {
						char cur = expression[c + varNameLength];
						if((cur < 'a' || cur > 'z') && (cur < 'A' || cur > 'Z') && (cur < '0' || cur > '9')) {
							c += varNameLength-1;
							break;
						}
						variableName[varNameLength] = expression[c + varNameLength];
					}
					char *const varNameStr = (char*)malloc(sizeof(char) * (varNameLength + 1));
					memcpy(varNameStr, variableName, varNameLength+1);

					AST *newAST = (AST*)malloc(sizeof(AST));
					newAST->type = AST_TYPE::VARIABLE;
					newAST->variableName = varNameStr;
					if(*lastAstElement == NULL) {
						astCollection = (AstCollection*)malloc(sizeof(AstCollection));
						lastAstElement = &(astCollection);
					} else {
						lastAstElement[0]->next = (AstCollection*)malloc(sizeof(AstCollection));
						lastAstElement = &(lastAstElement[0]->next);
					}
					lastAstElement[0]->ast = newAST;
					lastAstElement[0]->next = NULL;
					printf("Variable(%s); ", varNameStr);
					break;
				}
				break;
		}
		c++;
	}


	// Tokenization done; now building tree
	while(operations && astCollection->next) {
		Operation *mostSignificantOperation = operations; // most significant operator taking into account operator precedence
		for(Operation *currentOperation = operations; currentOperation; currentOperation = currentOperation->next) {
			switch(currentOperation->operation) {
				case '^':
					if(mostSignificantOperation->operation == '*' || mostSignificantOperation->operation == '/') {
						mostSignificantOperation = currentOperation;
						break;
					}
				case '*':
				case '/':
					if(mostSignificantOperation->operation == '+' || mostSignificantOperation->operation == '-') {
						mostSignificantOperation = currentOperation;
						break;
					}
				case '+':
				case '-':
					break;
			}
		}

		AstCollection *mostSignificantOperand = astCollection;
		{
			AstCollection *currentOperand = astCollection;
			for(Operation *currentOperation = operations; currentOperation; currentOperation = currentOperation->next) {
				if(currentOperation == mostSignificantOperation) {
					mostSignificantOperand = currentOperand;
					break;
				}
				currentOperand = currentOperand->next;
			}
		}

		{
			AST *combined = (AST*)malloc(sizeof(AST));
			combined->before = mostSignificantOperand->ast;
			combined->after = mostSignificantOperand->next->ast;
			combined->operation = mostSignificantOperation->operation;
			combined->type = AST_TYPE::EQUATION;

			mostSignificantOperand->ast = combined;
		}

		
		// remove obsolete AstCollection Object
		{
			AstCollection *obsoleteAST = mostSignificantOperand->next;
			mostSignificantOperand->next = mostSignificantOperand->next->next;
			free(obsoleteAST);
		}

		// remove obsolete Operation Object
		{
			Operation *obsoleteOperation = mostSignificantOperation;
			if(obsoleteOperation != operations) {
				Operation *beforeObsolete = operations;
				for(; beforeObsolete->next != obsoleteOperation; beforeObsolete = beforeObsolete->next);
				beforeObsolete->next = obsoleteOperation->next;
			} else if(operations->next != NULL) {
				operations = operations->next;
			} else
				operations = NULL;
			free(obsoleteOperation);
		}
	}

	if(astCollection->next) {
		printf("Error: Operands not fully resolved\n");
		return NULL;
	}

	printf(">");

	// free AstCollection object but keep AST
	AST *returnVal = astCollection->ast;
	free(astCollection);
	return returnVal;
}
#ifdef printf
	#undef printf // re-enable printf in case it was disabled before buildAST
#endif

void deleteAST(AST *const ast) {
	switch(ast->type) {
		case AST_TYPE::VARIABLE:
			free(ast->variableName);
			break;

		case AST_TYPE::EQUATION:
			deleteAST(ast->before);
			deleteAST(ast->after);
			break;
	}
	free(ast);
}


bool isAstStatic(const AST *const ast) {
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			return true;

		case AST_TYPE::VARIABLE:
			return false;

		case AST_TYPE::EQUATION:
			return isAstStatic(ast->before) && isAstStatic(ast->after);
	}
	printf("Error: isAstStatic(): Unsupported AST_TYPE enum value\n");
	*(int*)0 = 69; // Gracefully shutdown program
	return false;
}

float evalAstStatic(const AST *const ast) {
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			return ast->value;

		case AST_TYPE::VARIABLE:
			printf("Error: Trying to statically evaluate non-static AST\n");
			*(int*)0 = 420;
			return 0./0.;

		case AST_TYPE::EQUATION:
			const float val1 = evalAstStatic(ast->before);
			const float val2 = evalAstStatic(ast->after);
			return calc(val1, val2, ast->operation);
	}
	printf("Error: evalAstStatic(): Unsupported AST_TYPE enum value\n");
	*(int*)0 = 187; // Gracefully shutdown program
	return 0. / 0.; // NaN just to be sure and to please compiler
}

typedef struct sVariable Variable; // linked list of variables
struct sVariable {
	char *name;
	float value;
	Variable *next;
};

float getVariableValue(const Variable *variables, const char *const varName) { // sucht variabelnamen in linked list und gibt dazugehörigen Wert zurueck
	for(; variables; variables = variables->next)
		if(strcmp(variables->name, varName) == 0)
			return variables->value;
	printf("Error: Variable <%s> could not be resolved.\n", varName);
	return 0./0.; // NaN
}

void deleteVariables(Variable *variables) {
	while(variables) {
		Variable* obsolete = variables;
		variables = variables->next;
		free(obsolete->name);
		free(obsolete);
	}
}

Variable* extractAstVariablesPrimitive(const AST *const ast) { // may return same variable name multiple times
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			return NULL;

		case AST_TYPE::VARIABLE:
			{
				Variable *res = (Variable*)malloc(sizeof(Variable));
				res->name = (char*)malloc(sizeof(char)*(strlen(ast->variableName)+1));
				memcpy(res->name, ast->variableName, strlen(ast->variableName)+1);
				// printf("Found var: <%s>\n", res->name);
				res->next = NULL;
				return res;
			}

		case AST_TYPE::EQUATION:
			{
				Variable *lhs = extractAstVariablesPrimitive(ast->before);
				Variable *rhs = extractAstVariablesPrimitive(ast->after);
				// printf("Equation: <%s, %s>\n", lhs->name, rhs->name);
				if(!lhs)
					return rhs;
				Variable *lhsEnd = lhs;
				for(; lhsEnd->next; lhsEnd = lhsEnd->next); // lhs is a linked list, so find end to append to
				lhsEnd->next = rhs;
				return lhs;
			}
	}
	printf("Error: extractAstVariables(): Unsupported AST_TYPE enum value\n");
	*(int*)0 = 42; // Gracefully shutdown program
	return NULL; // Please compiler
}

Variable* extractAstVariables(const AST *const ast) { // remove duplicates from linked list
	Variable *variables = extractAstVariablesPrimitive(ast);
	for(Variable *currentVar = variables; currentVar; currentVar = currentVar->next) {
		Variable *beforeObsolete = currentVar;
		Variable *testVar = currentVar->next;

		for(; testVar; beforeObsolete = testVar, testVar = testVar->next) {
			if(strcmp(currentVar->name, testVar->name) == 0) {
				beforeObsolete->next = testVar->next;
				free(testVar->name);
				free(testVar);
				testVar = beforeObsolete;
			}
		}
	}
	return variables;
}

float evalAstDynamic(const AST *const ast, const Variable *const variables) {
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			return ast->value;

		case AST_TYPE::VARIABLE:
			return getVariableValue(variables, ast->variableName);

		case AST_TYPE::EQUATION:
			const float val1 = evalAstDynamic(ast->before, variables);
			const float val2 = evalAstDynamic(ast->after, variables);
			return calc(val1, val2, ast->operation);
	}
	printf("Error: evalAstStatic(): Unsupported AST_TYPE enum value\n");
	*(int*)0 = 187; // Gracefully shutdown program
	return 0. / 0.; // NaN just to be sure
}

void printFormulaDynamic(const AST *const ast, const Variable *const variables) {
	switch(ast->type) {
		case AST_TYPE::CONSTANT:
			printf("%f", ast->value);
			break;

		case AST_TYPE::VARIABLE:
			printf("%f", getVariableValue(variables, ast->variableName));
			break;

		case AST_TYPE::EQUATION:
			printf("(");
			printFormulaDynamic(ast->before, variables);
			printf(" %c ", ast->operation);
			printFormulaDynamic(ast->after, variables);
			printf(")");
			break;
	}
}

void printEval(const AST *const ast) {
	// Binaerbaum der Formel als geordneten Term ausdrucken
	printf("Formel: ");
	printFormula(ast);
	printf("\n");

	if(isAstStatic(ast)) {
		printf("Der term ist statisch.\n");
		printf("Ergebnis: %f\n", evalAstStatic(ast));
		return;// true;
	}

	printf("Der term ist variabel.\n");

	Variable *const variables = extractAstVariables(ast); // Variablennamen aus Binaerbaum extrahieren

	// Liste der gefundenen Variablen ausdrucken
	// printf("Variablen: {");
	// for(Variable *cur = variables; cur; cur = cur->next) {
	// 	printf("%s", cur->name);
	// 	if(cur->next)
	// 		printf(", ");
	// }
	// printf("}\n");

	// Werte fuer variablen einlesen
	printf("Bitte weisen sie den Variablen werte zu:\n");
	for(const Variable *currentVar = variables; currentVar; ) {
		printf("%s = ", currentVar->name);
		if(scanf("%f", &(currentVar->value)) != 1) {
			printf("Wert konnte nicht gelesen werden, bitte versuchen sie es erneut!\n");
			flushInput();
			continue;
		}
		currentVar = currentVar->next;
	}
	flushInput(); // Warum auch immer; Ansonsten ist der inputbuffer nach scanf nicht leer

	// Ausgewählte Variablenwerte ausgeben
	// printf("\nDie variablen sind:\n");
	// for(const Variable *currentVar = variables; currentVar; currentVar = currentVar->next)
	// 	printf("%s = %f\n", currentVar->name, currentVar->value);

	// Formel mit eingesetzten Variabelwerten ausgeben
	printf("\n");
	printf("Variablen einsetzen: ");
	printFormulaDynamic(ast, variables);
	printf("\n");

	printf("Ergebnis: %f\n", evalAstDynamic(ast, variables));

	deleteVariables(variables); // Speicher der linked list fuer Vriablen freigeben
}

void printEvalRepeat(const AST *const ast) { // repeated evaluation of function with different variables
	// Binaerbaum der Formel als geordneten Term ausdrucken
	printf("Formel: ");
	printFormula(ast);
	printf("\n");

	Variable *const variables = extractAstVariables(ast); // Variablennamen aus Binaerbaum extrahieren

	// Liste der gefundenen Variablen ausdrucken
	// printf("Variablen: {");
	// for(Variable *cur = variables; cur; cur = cur->next) {
	// 	printf("%s", cur->name);
	// 	if(cur->next)
	// 		printf(", ");
	// }
	// printf("}\n");

	for(;;) {
		// Werte fuer variablen einlesen
		printf("Bitte weisen sie den Variablen werte zu:\n");
		for(const Variable *currentVar = variables; currentVar; ) {
			printf("%s = ", currentVar->name);
			if(scanf("%f", &(currentVar->value)) != 1) {
				printf("Wert konnte nicht gelesen werden, bitte versuchen sie es erneut!\n");
				flushInput();
				continue;
			}
			currentVar = currentVar->next;
		}
		flushInput(); // Warum auch immer; Ansonsten ist der inputbuffer nach scanf nicht leer

		// Ausgewählte Variablenwerte ausgeben
		// printf("\nDie variablen sind:\n");
		// for(const Variable *currentVar = variables; currentVar; currentVar = currentVar->next)
		// 	printf("%s = %f\n", currentVar->name, currentVar->value);

		// Formel mit eingesetzten Variabelwerten ausgeben
		// printf("\n");
		// printf("Variablen einsetzen: ");
		// printFormulaDynamic(ast, variables);
		// printf("\n");

		printf("Ergebnis: %f\n", evalAstDynamic(ast, variables));


		char conf=0;
		printf("Erneut berechnen? (j / n) ");
		for(;;) {
			while(scanf("%c", &conf) != 1) {
				printf("Antwort nocht verstanden, bitte versuchen sie es erneut\n");
				flushInput();
			}
			if(conf == 'j' || conf == 'J')
				break;
			if(conf == 'n' || conf == 'N') {
				deleteVariables(variables); // Speicher der linked list fuer Vriablen freigeben
				return;
			}
			printf("Ungueltige antwort. Bitte versuchen sie es erneut\n");
		}
	}
	deleteVariables(variables); // Speicher der linked list fuer Vriablen freigeben
}

// float sqrtIter(const float sq, int iter) {
// 	float res = 1;
// 	for(; iter--; )
// 		res = (res + sq / res) / 2;
// 	return res;
// }

bool printAdvancedCalc(const char *const input) { // returns true on success
	// for(float n=1; n<=10.1; n++)
	// 	printf("sqrt(%f) = %f\n", n, sqrtIter(n, 5));
	// return true;

	const int CMD_INVALID = -1;
	const int CMD_TREE = 0;
	const int CMD_EVAL = 1;
	const int CMD_EVAL_REPEAT = 2;
	int cmd = CMD_INVALID;

	if(memcmp(input, "tree ", strlen("tree ")) == 0)
		cmd = CMD_TREE;
	else if(memcmp(input, "eval ", strlen("eval ")) == 0)
		cmd = CMD_EVAL;
	else if(memcmp(input, "eval_rep ", strlen("eval_rep ")) == 0)
		cmd = CMD_EVAL_REPEAT;

	if(cmd == CMD_INVALID) {
		printf("Advanced: Befehl nicht verstanden, bitte versuchen sie es erneut!\n");
		return false;
	}

	// parse function
	const int cmdLength = strchr(input, ' ') - input; // skip command when parsing method
	AST *const ast = buildAST(input+cmdLength, strlen(input+cmdLength));
	if(!ast) {
		printf("Error: buildAST returned nullptr\n");
		return false;
	}

	if(cmd == CMD_TREE) {
		printf("AST:\n");
		printAST(ast, 0); // Binaerbaum ausgeben
		printf("\n");
		deleteAST(ast); // Speicher des Binaerbaums freigeben
		return true;
	}

	if(cmd == CMD_EVAL) {
		printEval(ast);
		deleteAST(ast);
		return true;
	}

	if(cmd == CMD_EVAL_REPEAT) {
		printEvalRepeat(ast);
		deleteAST(ast);
		return true;
	}

	return false; // nicht erreichbar, sondern ein Opfer um den Compiler zu besaenftigen
}


// void testLeaks() {
// 	for(;;) {
// 		// printAdvancedCalc("1+2+3+4+5");
// 		const char *const input = "1+2+3+4+5";
// 		AST *const ast = buildAST(input, strlen(input));
// 		printAST(ast, 0);
// 		deleteAST(ast);
// 	}
// }