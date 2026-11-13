#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>
#include <time.h>

#define PIN 17
#define MAX 76
#define MIN 68
#define MAX_READINGS 100

double calcAverage(double readings[], int count)
{
	double total = 0;
	for (int i = 0; i < count; i++) 
	{
		total += readings[i];
	}
	return total / count;
}

void readings(double readings[], int count) 
{	
	printf("Temperature Readings:\n");
	for (int i = 0; i < count; i++) 
	{
		printf("%.1f F\n", readings[i]);
	}
}

int isOutOfRange(double temperature)
{
	return (temperature > MAX || temperature < MIN) ? 1 : 0;
}

void checkReadings(double readings[], int count)
{
	printf("\nReadings that need attention:\n");
	for (int i = 0; i < count; i++)
	{
		if (isOutOfRange(readings[i]))
		{
			printf("%.1F\n\n", readings[i]);
		}
	}
}

int testsRun = 0;
int testsPassed = 0;

void recordTest(const char *testName, int passed)
{
	testsRun++;
	if (passed) 
	{
		testsPassed++;
		printf("PASS: %s\n", testName);
	} 
	else 
	{
		printf("FAIL: %s\n", testName);
	}
}

const char* getStatus(double temperature)
{
	if(isOutOfRange(temperature))
	{
		gpioWrite(PIN,1); // LED ON
		return "WARNING";
	}
	else
	{
		gpioWrite(PIN,0); // LED OFF
		return "NORMAL";
	}
}

void saveReadings(double readings[], int count)
{
	FILE *FH = fopen("readings.txt", "w");
	char tempText[20];
	const char *ledStatus;
	if (FH == NULL)
	{
		printf("Error: File could not open readings.txt\n");
		exit(0);
	}
	
	fprintf(FH, "%-15s %-15s %-10s\n", "Temperature", "System Statuses", "Warning LED");
	
	for (int i = 0; i < count; i++)
	{
		sprintf(tempText, "%.1fF", readings[i]); 
		if (isOutOfRange(readings[i]))
		{
			ledStatus = "ON";
		}
		else
		{
			ledStatus = "OFF";
		}
		
		fprintf(FH, "%-15s %-15s %-10s\n", tempText, getStatus(readings[i]), ledStatus);
	
	}
	
	fclose(FH);
}
	
			

/*void test_T1(void) {
	double temperature = 76.0;
	recordTest("test",
				isOutOfRange(temperature) == 1);
}*/


int main(int argc, char* agrv[])
{
	int numReadings = 0;
	double temp = 0;
	double tempReadings[MAX_READINGS];
	int result;
	int c;
	gpioInitialise();
	gpioSetMode(PIN,PI_OUTPUT);
	
	do
	{
		
		printf("How many readings do you want to enter in? ");
		result = scanf("%d", &numReadings);
		while ((c = getchar()) != '\n' && c != EOF);
	}
	while (result != 1 || numReadings < 1 || numReadings > MAX_READINGS);
		
	
	for (int i = 0; i < numReadings; i++)
	{
		printf("Enter temperature %d in Fahrenheit: ", i + 1);
		scanf("%lf", &temp);
		gpioWrite(PIN,0); // LED OFF
		tempReadings[i] = temp;
		printf("%.1fF - %s - LED %s\n\n", temp, getStatus(temp),isOutOfRange(temp) ? "ON" : "OFF");
	}
	checkReadings(tempReadings, numReadings);
	
	printf("Average of your inputted temperature readings is: %.1fF\n", calcAverage(tempReadings, numReadings));
	
	saveReadings(tempReadings, numReadings);
	sleep(3);
	gpioWrite(PIN,0); // LED OFF
	gpioTerminate();
	
return 0;
}


