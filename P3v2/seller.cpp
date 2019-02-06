#include "seller.h"

//The constructor also creates the objects thread.
Seller::Seller(std::string auditorium[10][10], std::string type, int N) {
    //generate buyers
	for(int i = 0; i < N; i++) {
		Buyer b;
		createBuyer(&b, i);
		allBuyers.push_back(b);
		this->buyerQueue.push(b);
	}
    this->auditorium = auditorium;
	this->type = type;
	this->service_time = 0;
}

//Call this function to start running the sell function
//We use this so that we can create a thread when we instantiate a Seller
//could not figure out cleaner way to do this
//pseudo private
static void* _startSales(void* seller) {
    Seller* s = (Seller*) seller;
    printf("Starting seller thread for %s\n", s->type.c_str());
    return s->sell();
}

void Seller::StartSelling() {
	//create the thread
	pthread_create(&this->sellerThread, NULL, _startSales, (void*) this);
}

void Seller::printStarted(Transaction t) {
	std::string time_str = "0";
	if (timer >= 10) time_str = "";
	std::string bID = "0";
	if (t._b.ID >= 10) bID = "";

	pthread_mutex_lock(&std_output);
	std::cout << "0:" << time_str << timer;
	std::cout << " Customer " << bID << t._b.ID;
	std::cout << " is being served from seller ";
	std::cout << type;
	std::cout << "and is assigned seat: R" << t.row << "C" << t.col;
	std::cout << std::endl;
	std::cout << "WILL FINISH AT: " << t.time << std::endl;
	pthread_mutex_unlock(&std_output);
}

void Seller::finishSale(Transaction t) {
	std::string time_str = "0";
	if (timer >= 10) time_str = "";
	std::string bID = "0";
	if (t._b.ID >= 10) bID = "";

	pthread_mutex_lock(&std_output);
	std::cout << "0:" << time_str << timer;
	std::cout << " Customer " << bID << t._b.ID;
	std::cout << " has finished buying from seller ";
	std::cout << type;
	std::cout << " with seat: R" << t.row << "C" << t.col;
	std::cout << std::endl;
	pthread_mutex_unlock(&std_output);

	//customer takes the seat
	std::string seat_string = "";
	seat_string += this->type;
	if (t._b.ID < 10) seat_string += "0";
	seat_string += std::to_string(t._b.ID);
	pthread_mutex_lock(&selling_mutex);
	this->auditorium[t.row][t.col] = seat_string;
	pthread_mutex_lock(&std_output);
	printAuditorium(this->auditorium);
	printf("\n");
	pthread_mutex_unlock(&std_output);
	// increment the number of customers that got seats
	this->increaseBuyerCount();
	pthread_mutex_unlock(&selling_mutex);
}

void* Seller::sell() {
    //take mutexs
	pthread_mutex_lock(&mutex_condition);
	pthread_cond_wait(&cond_go, &mutex_condition);
	pthread_mutex_unlock(&mutex_condition);
    //run untill timeris done
	//int next_buy_time= timer; // AND GET RID OF THISvvv
	while(timer < MAXIMUM_RUN_TIME) {
		int next_buy_time= timer; // IF STOPS WORKING UNCOMMENT THIS^^
		// check if it is time to serve the next customer and that the queue is not empty
		if( (!this->buyerQueue.empty()) && (timer >= next_buy_time) && (timer >= buyerQueue.top().arrived)) {
			//its time
            //Lock the sale here!
			pthread_mutex_lock(&selling_mutex);
			Buyer b = this->buyerQueue.top();
			this->buyerQueue.pop();
			// Here we get the service time for the customer
			int customer_buy_wait_time = sellerRandomSellTime();


            //if we still have tickets
			if(tickets_for_sale-- > 0) {
				// customer is being serviced so set next available time
				next_buy_time+= customer_buy_wait_time;
                int row = currentRow();
                int col = currentColumn();
                getNewSeat();
                //continue searching for new seat if not empty
                while(this->auditorium[row][col] != "-") {
                    //break if about to leave auditorium ie seller has used up all spots
                	if (this->checkIfDone()) {
                        break;
                    }
                    row = currentRow();
                    col = currentColumn();
                    getNewSeat();
                }

				// CHANGES MADE
				Transaction t = Transaction(b, timer + customer_buy_wait_time, row, col);
				printStarted(t);
				transactions.push_back(t);

				//pthread_mutex_unlock(&selling_mutex);
				//pthread_mutex_lock(&selling_mutex);

				//print info of payment
                //printTime(timer);
                // printf("\n");
				// printPurchase(&b, this->type.c_str());
				// //customer takes the seat
                // std::string seat_string = "";
                // seat_string += this->type;
                // seat_string += "0";
                // seat_string += std::to_string(b.ID);
				// this->auditorium[row][col] = seat_string;
				// printAuditorium(this->auditorium);
				// printf("\n");
				// // increment the number of customers that got seats
				// this->increaseBuyerCount();
			}
            //Else there are no tickets
			else {
				pthread_mutex_lock(&std_output);
                printTime(timer);
                printf("\n");
				printSoldout(timer, &b, this->type.c_str());
				pthread_mutex_unlock(&std_output);
				++turned_away_customers;
			}
            //release mutex
			pthread_mutex_unlock(&selling_mutex);
		}

		while (!transactions.empty()) {
			for (int i = 0; i < transactions.size(); i++) {
				if (timer >= transactions[i].time) {
					//pthread_mutex_lock(&selling_mutex);
					finishSale(transactions[i]);
					//pthread_mutex_unlock(&selling_mutex);
					transactions.erase(transactions.begin() + i);
					i--;
				} else sleep(0.5);
			}
		}
	}
	//std::cout << "!!!COMPLETED: " << type << std::endl;
	return NULL;
}

bool Seller::checkIfDone() {
    if(this->type[0] == 'H') {
        if (9 < H_CURRENT_ROW) {
			return true;
        }
	}
	else if(this->type[0] == 'M') {
        if (0 > M_CURRENT_ROW) {
			return true;
            }
		}
		else if(this->type[0] == 'L') {
            if(0 > L_CURRENT_ROW) {
				return true;
            }
		}
    return false;
}

void Seller::increaseBuyerCount() {
    // increment the number of customers that got seats
	if(this->type[0] == 'H') {
		H_CUSTOMERS_WITH_SEATS++;
	}
	else if(this->type[0] == 'M') {
		M_CUSTOMERS_WITH_SEATS++;
	}
	else if(this->type[0] == 'L') {
		L_CUSTOMERS_WITH_SEATS++;
	}
}
//gets the new time
int Seller::sellerRandomSellTime() {
	if(this->type[0] == 'H') { //H sellers are 1 or 2 minutes
		return ((rand() % 2) + 1);
	}
	else if(this->type[0] == 'M') { //M sellers are 2 3 or 4 minutes
		return ((rand() % 3) + 2);
	}
	else if(this->type[0] == 'L') {
		return ((rand() % 4) + 4); //L sellers are 4 5 6 or 7 minutes
	}
}

// get the current row for seating
// requires getting the lock prior to its call
int Seller::currentRow() {

	if(this->type[0] == 'H') {
		return H_CURRENT_ROW;
	}
	else if(this->type[0] == 'M') {
		return M_CURRENT_ROW;
	}
	else if(this->type[0] == 'L') {
		return L_CURRENT_ROW;
	}
}


int Seller::currentColumn() {
	if(this->type[0] == 'H') {
		return H_CURRENT_SEAT;
	}
	else if(this->type[0] == 'M') {
		return M_CURRENT_SEAT;
	}
	else if(this->type[0] == 'L') {
		return L_CURRENT_SEAT;
	}

}

void Seller::getNewSeat() {
	if(this->type[0] == 'H') {
		++H_CURRENT_SEAT;
		//end of row
		if(H_CURRENT_SEAT > 9) {
			H_CURRENT_SEAT = 0;
			H_CURRENT_ROW++;
		}
	}

	else if(this->type[0] == 'L') {
		++L_CURRENT_SEAT;
		//end of row
		if(9 < L_CURRENT_SEAT) {
			L_CURRENT_SEAT = 0;
			L_CURRENT_ROW--;
		}
	}
    else if(this->type[0] == 'M') {
		++M_CURRENT_SEAT;
		if(9 < M_CURRENT_SEAT) {
			M_CURRENT_SEAT = 0;
			//HAS TO BE a better way to do this
            //Essentially handling the M oscillation behaviour
            //so messy
			if(5 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 6;
			}
			else if(6 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 4;
			}
			else if(4 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 7;
			}
			else if(7 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 3;
			}
			else if(3 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 8;
			}
			else if(8 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 2;
			}
			else if(2 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 9;
			}
			else if(9 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 1;
			}
			else if(1 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 0;
			}
			else if(0 == M_CURRENT_ROW) {
				M_CURRENT_ROW = -1;
			}
		}
	}
}

void Seller::printAvailables(int ctime) {
	std::string time = "0";
	if (ctime >= 10) time = "";

	for (int i = 0; i < allBuyers.size(); i++) {
		if (ctime >= allBuyers[i].arrived) {
			std::string bID = "0";
			if (allBuyers[i].ID >= 10) bID = "";

			pthread_mutex_lock(&std_output);
			std::cout << "0:" << time << ctime;
			std::cout << " Customer " << bID << allBuyers[i].ID;
			std::cout << " arrived at the tail of seller " << type;
			std::cout << "'s queue." << std::endl;
			pthread_mutex_unlock(&std_output);

			allBuyers.erase(allBuyers.begin() + i);
			i--;
		}
	}
}
