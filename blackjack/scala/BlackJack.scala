/*
 * BlackJack.scala
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */


package com.draga.blackjack.BlackJack

import com.draga.blackjack.Cards._

object CardWrapper {
   implicit def wrapCard(c: Card) = new CardWrapper(c)
}
import CardWrapper._

class CardWrapper (val card: Card) {
  def value : Int = card.v match {
    case Ace => 1
    case Two => 2
    case Three => 3
    case Four => 4
    case Five => 5
    case Six => 6
    case Seven => 7
    case Eight => 8
    case Nine => 9
    case Ten => 10
    case Jack => 10
    case Queen => 10
    case King => 10
  }
}

class Hand (d : Boolean) {
  var cards : List[Card] = List()
  val dealer = d
  // this is here to support eventual splitting of hands
  var bet : Double = 0

  // add a card to a hand
  def add(card : Card) { cards = card :: cards }
  
  // discard all cards from a hand
  def muck { cards = List() }

  // hit a hand, and return new value
  def hit : Int = {
    val card = Shoe.draw
    println(card)
    add(card)
    showValue(true)
    if (busted) {
      println("[BUST]")
      0
    } else {
      value
    }
  }

  // pretty print a hand
  // if a hand has a card in the hole, set `reveal' to true to show that hand,
  // otherwise card is kept hidden
  def show (reveal : Boolean) {
    if (cards.length == 0) {
      println("[no cards]")
    } else {
      if (reveal || !dealer)
	println(" " + cards(0))
      else
	println(" one face down card")

      cards.tail.foreach(c => println(" " + c))

      showValue(reveal)
    } 
  }

  // print value of a hand
  // will show `Total Value: ???' if hand has a card in the hole and
  // `reveal' is false
  def showValue(reveal : Boolean) {
    if (dealer && !reveal) {
      println("Total value: ???")
    } else {
      println("Total value: " + (values mkString "/"))
    }
  }

  // return true if a hand is busted
  def busted : Boolean = { value == 0 }

  // return true if a hand is blackjack
  def blackjack : Boolean = {(cards.length == 2) && (value == 21)}

  // return all possible values for a hand, considering aces

  def values : List[Int] = {
    var v = cards.map(c => c.value).reduceLeft((a, b) => a + b)
    var handval = List(v)

    def isAce(c : Card) : Boolean = (c.value == 1)

    for (x <- cards.filter(isAce)) {
      handval = handval.flatMap(a => List(a, a+10))
    }
    handval.sort((a,b) => a < b).removeDuplicates
  }

  // return the best non-busted value for a hand, considering aces
  // returns zero if hand is busted
  def value : Int = {
    val good = values.filter(21 >=)
    if (good == List()) 0 else good.reduceLeft(Math.max)
  }
}
