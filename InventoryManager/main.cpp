#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Item {
public:
	std::string name;
	int quantity;

	Item(const std::string& Name, int Quantity) {
		name = Name;
		quantity = Quantity;
	}

	void print() {
		std::cout << name << ' ';
		std::cout << quantity << '\n';
	}
};

class Inventory {
public:
	std::vector<Item>Items;

	int addItem(const std::string& name, int qty, int &Index) {
		if (Items.size() == 0) {
			Item newItem(name, qty);
			Items.push_back(newItem);
			return 0;
		}

		for (int i = 0; i < Items.size(); ++i) {
			if (Items[i].name == name) {
				Items[i].quantity += qty;
				Index = i;
				return 1;
			}
		}

		Item newItem(name, qty);
		Items.push_back(newItem);

		return 0;
	}

	int removeItem(const std::string& name, int qty, int& Index) {
		int sub;

		if (Items.size() > 0) {
			for (int i = 0; i < Items.size(); ++i) {
				if (Items[i].name == name) {
					sub = Items[i].quantity - qty;
					if (sub > 0) {
						Items[i].quantity -= qty;
						Index = i;
						return 0;
					}
					else if (sub == 0) {
						Items.erase(Items.begin() + i);
						return 1;
					}
					return -1;
				}
			}
		}

		return -2;
	}

	void printInventory() {
		for (Item it : Items) {
			it.print();
		}
	}

	int findItem(std::string name) {
		for (int i = 0; i < Items.size(); ++i) {
			if (Items[i].name == name) {
				return i;
			}
		}
		return -1;
	}
};
int main() {
	std::string input;
	std::string cmd;

	std::string name;
	int quantity;

	bool UserWantsToQuit = false;

	Inventory inventory;

	int exitCode;
	int itemIndex;

	std::string cmdMsg =
		std::string("You can use the following commands: \n") +
		std::string("1. add <item name> <item quantity> \n") +
		std::string("2. remove <item name> <item quantity> \n") +
		std::string("3. list \n") +
		std::string("4. search <item name> \n") +
		std::string("5. quit \n");

	std::cout << cmdMsg;

	do {
		std::cout << '>';
		std::getline(std::cin, input);
		std::stringstream ss(input);

		ss >> cmd;

		if (cmd == "add") {
			if (!(ss >> name >> quantity)) {
				std::cerr << "Error: 'add' command requires a name and a quantity.\n";
				continue;
			}
			else if (quantity <= 0) {
				std::cerr << "Error: item's quantity cannot be negative. \n";
				continue;
			}

			exitCode = inventory.addItem(name, quantity, itemIndex);

			if (exitCode == 0) {
				std::cout << "New item was added. \n";
			}
			else {
				std::cout << "Item '" << name << "' quantity was added to " << inventory.Items[itemIndex].quantity << '\n';
			}
		}
		else if (cmd == "remove") {
			if (!(ss >> name >> quantity)) {
				std::cerr << "Error: 'remove' command requires a name and a quantity.\n";
				continue;
			}
			else if (quantity <= 0) {
				std::cerr << "Error: item's quantity cannot be negative. \n";
				continue;
			}

			exitCode = inventory.removeItem(name, quantity, itemIndex);

			if (exitCode == 0) {
				std::cout << "Item '" << name << "' quantity was reduced to " << inventory.Items[itemIndex].quantity << '\n';
			}
			else if (exitCode == 1) {
				std::cout << "Item '" << name << "' was removed due to no quantity left. \n";
			}
			else if (exitCode == -1) {
				std::cerr << "Error: item's quantity cannot be negative. \n";
			}
			else {
				std::cerr << "Error: item was not found. \n";
			}
		}
		else if (cmd == "list") {
			if (inventory.Items.size() == 0) {
				std::cerr << "Error: empty inventory. \n";
			}

			inventory.printInventory();
		}
		else if (cmd == "search") {
			if (!(ss >> name)) {
				std::cerr << "Error: 'search' command requires a name. \n";
				continue;
			}

			int index = inventory.findItem(name);

			if (index == -1) {
				std::cerr << name << " was not found. \n";
				continue;
			}

			std::cout << "Item '" << name << "' was found. \n";
			std::cout << name << "'s quantity: " << inventory.Items[index].quantity << '\n';
		}
		else if (cmd == "quit") {
			UserWantsToQuit = true;
		}
		else {
			std::cerr << "Invalid command! \n";
		}
	} while (!UserWantsToQuit);

	std::cout << "Goodbye! \n";
	std::cout << "Exiting... \n";

	return 0;
}