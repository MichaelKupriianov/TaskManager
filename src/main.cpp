#include"Task.h"
#include"TaskManager.h"
#include"id/TaskId.h"
#include"subsidiary/convert.h"
#include"subsidiary/print.h"

int main() {
    TaskManager manager;
    manager.Add(Task::Create("first", ToPriority("high"), ToTime("12:00 17/12/2021")));
    manager.Add(Task::Create("second", ToPriority("low"), ToTime("23:00 12/11/2021")));
    manager.Add(Task::Create("third", ToPriority("none"), ToTime("11:15 5/12/2021")));
    Print(manager);
    manager.Complete(TaskId::Create(2));
    Print(manager.getTask(TaskId::Create(1)));
    manager.Delete(TaskId::Create(1));
    manager.Add(Task::Create("fourth", ToPriority("medium"), ToTime("14:00 10/5/2022")));
    manager.Edit(TaskId::Create(0), Task::Create("fifth", ToPriority("high"), ToTime("5:05 3/4/2022")));
    Print(manager);
}
