#include <array>
#include <utility>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

#define ACTION_NUM 3
#define STATE_NUM 3

enum State { STABLE = 0, TOO_MUCH_PRESSURE, TOO_LITTLE_PRESSURE };
enum Action { WAIT = 0, ADD_WATER, RELEASE_WATER };
std::array<std::array<float, ACTION_NUM>, STATE_NUM> LM = { {0} };
std::array<std::string, ACTION_NUM> action_to_string = { "WAIT", "ADD WATER", "RELEASE WATER" };
std::array<std::string, ACTION_NUM> state_to_string = { "STABLE", "TOO MUCH PRESSURE", "TOO LITTLE PRESSURE" };


void printMatrix()
{
	using namespace std;
	cout << "Q Matrix" << endl << endl;
	for (int i = 0; i < STATE_NUM; i++)
	{
		for (int j = 0; j < ACTION_NUM; j++)
		{
			cout << "For state \"" << state_to_string[i] << "\" the action \"" << action_to_string[j] << "\" has a value of: " << LM[i][j] << endl;
		}
	}
}

enum State selectState(float system_pressure)
{
	if (system_pressure < 25.0f)
	{
		return State::TOO_LITTLE_PRESSURE;
	}
	else if (system_pressure > 75.0f)
	{
		return State::TOO_MUCH_PRESSURE;
	}
	else if (system_pressure > 25.0f && system_pressure < 75.0f)
	{
		return State::STABLE;
	}
}

int main()
{
	srand(time(NULL));

	float system_pressure = 50.f;

	int iterator = 0;

	int chosen_action;

	while (system_pressure > 0)
	{
		std::cout << "System pressure is sitting at: " << system_pressure << "." << std::endl;

		// Describe State
		// TODO: Store a local variable that describes the current state
		enum State currentState = selectState(system_pressure);
		// Choose Action
		// TODO: Store a local variable that explains what action the AI will perform
		float bestValue = LM[currentState][0];

		int random_value = rand() % 100;
		// use a for loop to go through all the actions 
		for (int i = 0; i < ACTION_NUM; i++)
		{
			
			if (LM[currentState][i] > bestValue && random_value > 10)
			{
				//replace best value
				bestValue = LM[currentState][i];
				chosen_action = i;
			}
			else if (random_value < 10)
			{
				bestValue = LM[i][i];
				chosen_action = i;
			}
			
		}
		
		// Perform the Action
		// TODO: Implement the chosen action. Use a switch statement or function to manage this.
		int reward;
		switch (chosen_action)
		{
		case Action::WAIT:
			// TODO: Add code
			//good reward
			reward = 1;
			break;
		case Action::ADD_WATER:
			// TODO: Add code
			system_pressure += 10.f;
			//negative reward
			reward = -1;
			//change reward based off how far the system pressure is
			//if it over shoots pressure less of a reward
			break;
		case Action::RELEASE_WATER:
			// TODO: Add code
			system_pressure -= 10.f;
			//negative reward
			reward = -1;
			break;
		default:
			// We should never reach this point
			// but its good to prepare for it just in case
			break;
		}
		// Calculate Reward
		// TODO: Calculate the reward you want to give to the AI

		// Update Q Matrix
		// TODO: Update the correct item the Q matrix with the correct reward.
		LM[currentState][chosen_action] += reward;
		// TODO: Print out which action the AI ran. You can use a similar method to the action_to_string or state_to_string described in the printMatrix function

		
		
		system_pressure -= (rand() % 4);
		std::cout << "System has lost some pressure." << std::endl;
		std::this_thread::sleep_for(500ms);
		iterator++;
	}

	printMatrix();

	std::cin.get();
}