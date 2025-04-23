Assignment Question 10: Smart Bridge Load Monitor 

Scenario: You’re designing a Smart Bridge Load Monitor to track bridge components (e.g., "Beam", "Cable", "Deck", "Pylon", "Joint") for safety. The system uses:
●	Load Request System (Queue): Load tests queue up from sensors.
●	Stress Alert System (Stack): Critical stresses stack in LIFO order for immediate checks.
●	Load History Unit (Array): Test results log into an array-based database (size: 6 slots). If full, the oldest is archived.
●	Maintenance Tracker (Linked Lists):
○	Stressed components go to a singly linked list.
○	Reinforced components move to a doubly linked list for review.
○	High-priority components cycle in a circular linked list for urgent repairs.
Objective: Simulate load monitoring, logging, and component maintenance.
Tasks:

a) Load and Stress 
●	Simulate 6 load tests (e.g., "Beam", "Cable", "Deck", "Pylon", "Joint", "Bolt") arriving in a queue.
●	Stack critical stresses in LIFO order. Write pseudocode or an algorithm to:
○	Enqueue all 6 tests.
○	Dequeue and push onto a stack.
○	Pop to show check order.
●	Creativity Bonus: Describe (in 2-3 sentences) why LIFO fits (e.g., "Bolt" last to ensure structural integrity).
b) Load History Unit 
●	Log results in a 6-slot array.
●	Simulate logging 8 results (e.g., "Res1", "Res2", ..., "Res8"). If full, archive the oldest. Write pseudocode or an algorithm to:
○	Insert the first 6 results.
○	Handle overflow for "Res7" and "Res8".
●	Creativity Bonus: Suggest (in 2-3 sentences) a reason for archiving (e.g., regulatory audits).
c) Stressed Component Tracker 
●	"Cable" and "Joint" are stressed. Add to a singly linked list.
●	Move "Cable" to a doubly linked list post-reinforcement. Write pseudocode or an algorithm to:
○	Insert "Cable" and "Joint".
○	Delete "Cable" and insert it into the doubly linked list.
○	Traverse forward and backward.
●	Creativity Bonus: Propose (in 2-3 sentences) a stress cause and fix (e.g., "Cable stretched by wind, tensioned by bots").
d) Priority Repairs 
●	"Beam" and "Pylon" need urgent repairs (e.g., cracks). Add to a circular linked list. Write pseudocode or an algorithm to:
○	Insert "Beam" and "Pylon".
○	Traverse twice.
●	Creativity Bonus: Invent (in 2-3 sentences) a repair tweak (e.g., "Pylon gets a vibration damper").
