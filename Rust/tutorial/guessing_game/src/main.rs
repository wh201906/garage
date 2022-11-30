use rand::Rng;
use std::cmp::Ordering;

fn main() {
    let target = rand::thread_rng().gen_range(1..=100);
    loop {
        println!("Guess the number:");
        let mut input: String = String::new();
        std::io::stdin().read_line(&mut input).expect("error");

        // let num: i32 = input.trim().parse().expect("Not a number!");
        let num: i32 = match input.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input!");
                continue;
            }
        };
        match num.cmp(&target) {
            Ordering::Less => println!("{num} is too small!"),
            Ordering::Greater => println!("{num} is too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}
