use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Guess the number!");

    // `1..=100` is a range expression, contains 1 and 100
    let secret_number = rand::thread_rng().gen_range(1..=100);
    // the type of `"emmm"` is `&str`, not `str`
    let err_msg = "Please type a number!";

    println!("The secret number is: {secret_number}");

    println!("Please input your guess.");

    let mut guess = String::new();

    std::io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    println!("You guessed: {guess}");

    // the type of `"hello"` is `&str`, not `String`.
    // `guess` there contains the newline, use `trim()` to get the slice without newline.
    // the result of `guess.trim()` is `&str`
    // `&` is necessary there.
    match guess.trim().cmp(&"hello".to_string()) {
        Ordering::Less => println!("Unmatched"),
        Ordering::Greater => println!("Unmatched"),
        Ordering::Equal => println!("Matched"),
    }

    // guess.trim().parse() -> Result<F, <F as FromStr>::Err>
    // guess.trim().parse::<i32>() -> Result<i32, <i32 as FromStr>::Err>
    // guess.trim().parse::<i32>().expect("...") -> i32
    // guess.trim().parse().expect("...") -> T
    // `a.cmp(&b)` takes `&b` as argument, not b
    // calling `parse::<i32>()` there implicitly specifies the type of `secret_number` as `i32`
    match guess
        .trim()
        .parse::<i32>()
        .expect("Please type a number!")
        .cmp(&secret_number)
    {
        Ordering::Less => println!("Too small"),
        Ordering::Greater => println!("Too big"),
        Ordering::Equal => println!("You win"),
    }

    // reversed way
    match secret_number.cmp(&guess.trim().parse::<i32>().expect(err_msg)) {
        Ordering::Less => println!("Too big"),
        Ordering::Greater => println!("Too small"),
        Ordering::Equal => println!("You win"),
    }

    // "shadowing" there
    // "function ovarloading" there?
    let guess: i32 = guess.trim().parse().expect(err_msg);
    match guess.cmp(&secret_number) {
        Ordering::Less => println!("Too small"),
        Ordering::Greater => println!("Too big"),
        Ordering::Equal => println!("You win"),
    }
}
