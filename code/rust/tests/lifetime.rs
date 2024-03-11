use std::cell::RefCell;
use std::rc::Rc;
/* 链表节点类 */
#[derive(Debug)]
struct ListNode<T> {
    val: T,                            // 节点值
    next: Option<Rc<RefCell<ListNode<T>>>>, // 指向下一节点的指针
}

impl Drop for ListNode<T> {
    fn drop(&mut self) {
        println!("Dropping node {}", self.val);
    }
}

fn find<T: PartialEq>(head: Rc<RefCell<ListNode<T>>>, target: T, index: i32) -> i32 {
    if head.borrow().val == target {return index};
    if let Some(node) = &head.borrow_mut().next {
        return find(node.clone(), target, index + 1);
    }
    return -1;
}
#[test]
fn test_ll() {
    /* 初始化链表 1 -> 3 -> 2 -> 5 -> 4 */
    // 初始化各个节点
    let n0 = Rc::new(RefCell::new(ListNode { val: 1, next: None }));
    let n1 = Rc::new(RefCell::new(ListNode { val: 3, next: None }));
    let n2 = Rc::new(RefCell::new(ListNode { val: 2, next: None }));
    let n3 = Rc::new(RefCell::new(ListNode { val: 5, next: None }));
    let n4 = Rc::new(RefCell::new(ListNode { val: 4, next: None }));

    // 构建引用指向
    {
        n0.borrow_mut().next = Some(n1.clone());
        n1.borrow_mut().next = Some(n2.clone());
        n2.borrow_mut().next = Some(n3.clone());
        n3.borrow_mut().next = Some(n4.clone());
    }
    
}
