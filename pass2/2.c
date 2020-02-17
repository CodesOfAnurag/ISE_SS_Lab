//Pass-2 of two-pass assembler
#include <stdio.h>
#include <string.h>

void main()
{
	FILE *interip, *optab, *symtab, *output;
	char label[20], opcode[20], operand[20];
	int address, sa, len, i;
	interip = fopen("interip.txt", "r");
	output = fopen("output.txt", "w");
	fscanf(interip, "%x %s %s %s", &address, label, opcode, operand);
	if (strcmp(opcode, "START") == 0)
	{
		fprintf(output, "%X\t%s\t%s\t%s\t-\n", address, label, opcode, operand);
		sa = address;
	}

	fscanf(interip, "%x %s %s %s", &address, label, opcode, operand);

	while (strcmp(opcode, "END") != 0)
	{
		fprintf(output, "%X\t%s\t%s\t%s\t", address, label, opcode, operand);
		
		// to get the opcode viz 1 byte - 2 hex char
		// it checks the opp from optable and returns opcode
		optab = fopen("optab.txt", "r");
		char tempcode[20], tempval[20];
		fscanf(optab, "%s %s", tempcode, tempval);
		while (!feof(optab))
		{
			if (strcmp(opcode, tempcode) == 0)
			{
				fprintf(output, "%s", tempval);
				break;
			}
			else
				fscanf(optab, "%s %s", tempcode, tempval);
		}
		fclose(optab);

		// checks for index mode
		// takes out the symbol from the operand for
		// getting its initial address of the operand from symtab
		char actoperand[20];
		strcpy(actoperand, "");
		if (operand[strlen(operand) - 1] == 'X')
		{
			for (i = 0; i < strlen(operand) - 2; i++)
				actoperand[i] = operand[i];
			actoperand[i] = '\0';
		}
		else
			strcpy(actoperand, operand);

		symtab = fopen("symtab.txt", "r");
		char symcode[20], symval[20];
		fscanf(symtab, "%s %s", symcode, symval);
		while (!feof(symtab))
		{
			if (strcmp(actoperand, symcode) == 0)
			{

				int lval = strtol(symval, NULL, 16);
				if (operand[strlen(operand) - 1] == 'X')
					lval = lval + 0x8000;
				fprintf(output, "%X\n", lval);
				break;
			}
			else
				fscanf(symtab, "%s %s", symcode, symval);
		}
		fclose(symtab);

		// checks for assembler directives
		if (strcmp(opcode, "WORD") == 0)
		{
			// converts to hex
			int val = strtol(operand, NULL, 16);
			char num[10];
			sprintf(num, "%X", val);
			int l = strlen(num);
			//appending zeros to righthand-side
			while (l < 6)
			{
				fprintf(output, "0");
				l++;
			}
			fprintf(output, "%s\n", num);
		}

		if (strcmp(opcode, "BYTE") == 0)
		{
			if (operand[0] == 'X')
			{
				for (i = 2; i < strlen(operand) - 1; i++)
					fprintf(output, "%c", operand[i]);
				fprintf(output, "\n");
			}
			else if (operand[0] == 'C')
			{
				for (i = 2; i < strlen(operand) - 1; i++)
				{
					fprintf(output, "%02X", operand[i]);
				}
				fprintf(output, "\n");
			}
		}

		if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0)
			fprintf(output, "-\n");

		fscanf(interip, "%x %s %s %s", &address, label, opcode, operand);
	}
	fprintf(output, "%X\t%s\t%s\t%s\n", address, label, opcode, operand);

	len = address - sa;

	printf("\nOutput File generated as output.txt\n");

	fclose(interip);
	fclose(output);
}
