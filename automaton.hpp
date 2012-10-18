#ifndef META_AUTOMATON_HPP_INCLUDED
#define META_AUTOMATON_HPP_INCLUDED

#include <iostream>

#include "integral.hpp"
#include "list.hpp"
#include "bool.hpp"
#include "replace.hpp"
#include "append.hpp"
#include "get.hpp"
#include "length.hpp"
#include "bind.hpp"
#include "apply.hpp"
#include "map.hpp"
#include "exec.hpp"
#include "add.hpp"
#include "fold.hpp"
#include "compare.hpp"
#include "sort.hpp"
#include "filter.hpp"
#include "assoc.hpp"
#include "compose.hpp"

namespace meta {
  namespace automaton {
    template <typename Id = int_<0>,
	      typename Trans = nil>
    class state {
    public:
      typedef Id id;
      typedef Trans transitions;
    };

    class epsilon {};

    template <typename Char, typename State>
    class apply_trans {
      template <typename Transition, typename Accu>
      class fold_aux {
      public:
	typedef typename if_<typename is_same<typename Transition::character, Char>::type,
			     cons<typename Transition::state, Accu>,
			     Accu>::type type;
      };
    public:
      typedef typename fold<quote<fold_aux>,
			    typename State::transitions,
			    nil>::type type;
    };

    template <typename Char, typename State>
    class transition {
    public:
      typedef Char character;
      typedef State state; // id of state
    };

    template <typename States, typename Initial, typename Terminal>
    class fsm {
    public:
      typedef States states;
      typedef Initial initial;
      typedef Terminal terminal;
    };

    namespace __print {
      template <typename State>
      class print_state {
	template <typename Trans>
	class print_trans {
	public:
	  template <typename Stream>
	  static Stream& proc(Stream& stream) {
	    return stream << "S" << State::id::value << " -> S" << Trans::state::value
			  <<  " [ label = \"" << Trans::character::value << "\" ];"
			  << std::endl;
	  }
	};

	template <typename Target>
	class print_trans<transition<epsilon, Target> > {
	public:
	  template <typename Stream>
	  static Stream& proc(Stream& stream) {
	    return stream << "S" << State::id::value << " -> S" << Target::value
			  << ";" << std::endl;
	  }
	};

      public:
	template <typename Stream>
	static Stream& proc(Stream& stream) {
	  return fold_proc<print_trans, typename State::transitions>::proc(stream);
	}
      };

      template <typename Fsm>
      class print_fsm {
      public:
	template <typename Stream>
	static Stream& proc(Stream& stream) {
	  stream << "digraph finite_state_machine {" << std::endl
		 << "start [ label = \"\", shape = \"none\" ];" << std::endl
		 << "node [ shape = doublecircle ]" << std::endl
		 << "S" << Fsm::terminal::value << ";" << std::endl
		 << "node [ shape = circle ]" << std::endl
		 << "start -> S" << Fsm::initial::value << ";" << std::endl;
	  fold_proc<print_state, typename Fsm::states>::proc(stream);
	  return stream << "}" << std::endl;
	}
      };
    }

    template <typename Stream, typename... Args>
    Stream& operator<<(Stream& out, const fsm<Args...>&) {
      return __print::print_fsm<fsm<Args...> >::proc(out);
    }

    template <typename Fsm, typename N>
    class get_state {
    public:
      typedef typename get<typename Fsm::states, N>::type type;
    };

    template <typename Fsm, typename A, typename Char, typename B>
    class add_trans {
      typedef typename get_state<Fsm, A>::type a;
      typedef state<typename a::id,
		    typename add<transition<Char, B>, typename a::transitions>::type> a2;
    public:
      typedef fsm<typename replace<typename Fsm::states, A, a2>::type,
		  typename Fsm::initial,
		  typename Fsm::terminal> type;
    };

    template <typename Fsm, typename A, typename B>
    class add_eps_trans : public add_trans<Fsm, A, epsilon, B> {};

    namespace __new_states {
      template <typename From, typename To>
      class aux {
      public:
	typedef cons<state<From>, typename aux<int_<From::value+1>, To>::type> type;
      };

      template <typename X>
      class aux<X,X> {
      public:
	typedef nil type;
      };
    }

    template <typename Fsm, typename N>
    class new_states {
      typedef typename length<typename Fsm::states>::type from;
      typedef int_<from::value+N::value> to;
    public:
      typedef fsm<typename append<typename Fsm::states,
				  typename __new_states::aux<from,to>::type>::type,
		  typename Fsm::initial,
		  typename Fsm::terminal> type;
    };

    namespace __merge {
      template <typename N, typename Fsm>
      class shift {
	typedef bind<quote<plus>, int_<0>, N> plus_N;

	template <typename Transition>
	class shift_trans_N {
	public:
	  typedef transition<typename Transition::character,
			     typename apply<plus_N,
					    typename Transition::state>::type> type;
	};

	template <typename State>
	class shift_state_N {
	public:
	  typedef state<typename apply<plus_N,
				       typename State::id>::type,
			typename map<quote<shift_trans_N>,
				     typename State::transitions>::type> type;
	};

      public:
	typedef fsm<typename map<quote<shift_state_N>, typename Fsm::states>::type,
		    typename apply<plus_N, typename Fsm::initial>::type,
		    typename apply<plus_N, typename Fsm::terminal>::type> type;
      };
    }

    template <typename FsmA, typename FsmB>
    class merge {
      typedef typename length<typename FsmA::states>::type shift;
      typedef typename __merge::shift<shift, FsmB>::type FsmB2;
    public:
      typedef FsmA a;
      typedef FsmB2 b;
      typedef fsm<typename append<typename a::states, typename b::states>::type,
		  typename a::initial,
		  typename a::terminal> type;
    };

    typedef fsm<cons<state<>, nil>, int_<0>, int_<0> > fsm_epsilon;

    template <typename N>
    class create {
    public:
      typedef typename new_states<fsm<nil, int_<0>, int_<0> >, N>::type type;
    };

    template <typename Fsm, typename N>
    class set_terminal {
    public:
      typedef fsm<typename Fsm::states, typename Fsm::initial, N> type;
    };

    template <typename Fsm, typename N>
    class set_initial {
    public:
      typedef fsm<typename Fsm::states, N, typename Fsm::terminal> type;
    };

    template <char C>
    class fsm_char {
      typedef typename create<int_<2> >::type tmp1;
      typedef typename add_trans<tmp1, int_<0>, char_<C>, int_<1> >::type tmp2;
    public:
      typedef typename set_terminal<tmp2, int_<1> >::type type;
    };

    template <typename A, typename... B>
    class fsm_or {
    public:
      typedef typename fsm_or<A, typename fsm_or<B...>::type>::type type;
    };

    template <typename A, typename B>
    class fsm_or<A,B> {
      typedef typename merge<A,B>::a a;
      typedef typename merge<A,B>::b b;
      typedef typename merge<A,B>::type ab;
      typedef typename new_states<ab, int_<2> >::type t1;
      typedef typename length<typename t1::states>::type l;
      typedef int_<l::value-1> terminal;
      typedef int_<l::value-2> initial;
      typedef typename add_eps_trans<t1, initial, typename a::initial>::type t2;
      typedef typename add_eps_trans<t2, initial, typename b::initial>::type t3;
      typedef typename add_eps_trans<t3, typename a::terminal, terminal>::type t4;
      typedef typename add_eps_trans<t4, typename b::terminal, terminal>::type t5;
    public:
      typedef fsm<typename t5::states, initial, terminal> type;
    };

    template <typename A, typename B>
    class fsm_seq {
      typedef typename merge<A,B>::a a;
      typedef typename merge<A,B>::b b;
      typedef typename merge<A,B>::type t1;
    public:
      typedef typename set_terminal<typename add_eps_trans<t1,
							   typename a::terminal,
							   typename b::initial>::type,
				    typename b::terminal>::type type;
    };

    template <typename A>
    class fsm_star {
      typedef typename new_states<A, int_<2> >::type t1;
      typedef typename length<typename t1::states>::type l;
      typedef int_<l::value-1> terminal;
      typedef int_<l::value-2> initial;
      typedef typename add_eps_trans<t1,
				     typename t1::terminal,
				     typename t1::initial>::type t2;
      typedef typename add_eps_trans<t2, initial, typename t1::initial>::type t3;
      typedef typename add_eps_trans<t3, typename t1::terminal, terminal>::type t4;
      typedef typename add_eps_trans<t4, initial, terminal>::type t5;
    public:
      typedef fsm<typename t5::states, initial, terminal> type;
    };

    template <char... C>
    class fsm_string {
    public:
      typedef fsm_epsilon type;
    };

    template <char C, char... T>
    class fsm_string<C, T...> {
    public:
      typedef typename fsm_seq<typename fsm_char<C>::type,
			       typename fsm_string<T...>::type>::type type;
    };

    template <char A, char B>
    class fsm_range {
    public:
      typedef typename fsm_or<typename fsm_char<A>::type,
			      typename fsm_range<A+1, B>::type>::type type;
    };

    template <char A>
    class fsm_range<A,A> {
    public:
      typedef typename fsm_char<A>::type type;
    };

    namespace __closure {
      template <typename Fsm, typename Char, typename State, typename Accu>
      class aux {
	typedef typename if_<typename member<State, Accu>::type,
			     nil,
			     typename apply_trans<Char, typename get_state<Fsm, State>::type>::type>::type linked;
      public:
	typedef typename fold<bind<quote<fold>,
				   int_<0>,
				   quote<add> >,
			      typename map<bind<bind<bind<quote<aux>,
							  int_<3>,
							  cons<State, Accu> >,
						     int_<1>,
						     Char>,
						int_<0>,
						Fsm>,
					   linked>::type,
			      typename list::make<State>::type>::type type;
      };
    }

    template <typename Fsm, typename Char, typename States>
    class closure {
      typedef bind<bind<bind<quote<__closure::aux>,
			     int_<3>,
			     nil>,
			int_<1>,
			Char>,
      		   int_<0>,
      		   Fsm> aux;
      typedef typename if_<typename list::is<States>::type,
      			   States,
      			   typename list::make<States>::type>::type states;
      typedef typename fold<bind<quote<fold>,
      				 int_<0>,
      				 quote<add> >,
      			    typename map<aux, states>::type,
      			    nil>::type tmp;

    public:
      typedef typename sort<quote<compare::lt>, tmp>::type type;
    };

    template <typename States, typename Properties = nil>
    class dfsm {
    public:
      typedef States states;
      typedef Properties properties;
    };

    template <typename DFsm, typename Property>
    class get_property {
    public:
      typedef typename assoc<Property, typename DFsm::properties>::type type;
    };

    template <typename DFsm, typename... Properties>
    class set_property {
    public:
      typedef DFsm type;
    };

    namespace properties {
      class initial;
      class terminal;
    }

    template <typename DFsm, typename Property, typename Value, typename... Properties>
    class set_property<DFsm, Property, Value, Properties...> {
    public:
      typedef typename set_property<dfsm<typename DFsm::states,
					 cons<tuple<Property, Value>,
					      typename filter<compose<bind<quote<is_different>, int_<0>, Property>,
								      bind<quote<get>, int_<1>, int_<0> > >,
							      typename DFsm::properties>::type> >,
				    Properties...>::type type;
    };

    namespace __print {
      template <typename TerminalState>
      class print_terminal_aux {
      public:
	template <typename Stream>
	static Stream& proc(Stream& stream) {
	  return stream << "S" << TerminalState::value << ";" << std::endl;
	}
      };

      template <typename DFsm>
      class print_dfsm {
      public:
	template <typename Stream>
	static Stream& proc(Stream& stream) {
	  stream << "digraph deterministic_finite_state_machine {" << std::endl
		 << "start [ label = \"\", shape = \"none\" ];" << std::endl
		 << "node [ shape = doublecircle ]" << std::endl;
	  fold_proc<print_terminal_aux, typename get_property<DFsm, properties::terminal>::type>::proc(stream);
	  stream << "node [ shape = circle ]" << std::endl
		 << "start -> S" << get_property<DFsm, properties::initial>::type::value << ";" << std::endl;
	  fold_proc<print_state, typename DFsm::states>::proc(stream);
	  return stream << "}" << std::endl;
	}
      };
    }

    template <typename Stream, typename... Args>
    Stream& operator<<(Stream& out, const dfsm<Args...>&) {
      return __print::print_dfsm<dfsm<Args...> >::proc(out);
    }

    namespace __deterministic {
      template <typename Transition>
      class get_transition_char {
      public:
	typedef typename Transition::character type;
      };

      template <typename Fsm, typename State>
      class get_transitions {
      public:
	typedef typename map<quote<get_transition_char>,
			     typename get_state<Fsm, State>::type::transitions>::type type;
      };

      template <typename Fsm, typename Head, typename Tail>
      class get_transitions<Fsm, cons<Head, Tail> > {
      public:
	typedef typename fold<quote<add>,
			      typename get_transitions<Fsm, Head>::type,
			      typename get_transitions<Fsm, Tail>::type>::type type;
      };

      template <typename Fsm>
      class get_transitions<Fsm, nil> {
      public:
	typedef nil type;
      };
    }

    template <typename Fsm>
    class deterministic {
      template <typename State>
      class get_transitions {
      public:
	typedef typename filter<bind<quote<is_different>, int_<0>, epsilon>,
				typename __deterministic::get_transitions<Fsm, State>::type>::type type;
      };

      template <typename DFsm, typename Groups, typename Group>
      class get_det_state_found {
      public:
	typedef tuple<DFsm,
		      typename assoc<Group, Groups>::type,
		      Groups> type;
      };

      template <typename DFsm, typename Groups, typename Group>
      class get_det_state_not_found {
	typedef typename new_states<DFsm, int_<1> >::type fsm;
	typedef typename length<typename DFsm::states>::type state;
	typedef cons<tuple<Group, state>, Groups> groups;
      public:
	typedef tuple<fsm, state, groups> type;
      };

      template <typename DFsm, typename Groups, typename Group>
      class get_det_state {
	typedef typename if_<typename is_different<typename assoc<Group, Groups>::type, not_found>::type,
			     quote<get_det_state_found>,
			     quote<get_det_state_not_found> >::type aux;
	typedef typename apply<aux, DFsm, Groups, Group>::type tmp;

      public:
	typedef typename get<tmp, int_<0> >::type fsm;
	typedef typename get<tmp, int_<1> >::type state;
	typedef typename get<tmp, int_<2> >::type groups;
      };

      template <typename Group, typename Char>
      class apply_trans_group {
      public:
	typedef typename fold<bind<quote<fold>,
				   int_<0>,
				   quote<add> >,
			      typename map<bind<quote<apply_trans>, int_<0>, Char>,
					   typename map<bind<quote<get_state>, int_<0>, Fsm>, Group>::type>::type,
			      nil>::type type;
      };

      template <typename DFsm, typename Groups, typename GroupA, typename Char>
      class add_det_trans {
	typedef typename closure<Fsm,
				 epsilon,
				 typename apply_trans_group<GroupA, Char>::type>::type GroupB;
	typedef get_det_state<DFsm, Groups, GroupA> auxA;
	typedef get_det_state<typename auxA::fsm, typename auxA::groups, GroupB> auxB;
	typedef typename auxB::groups new_groups;
	typedef typename auxA::state stateA;
	typedef typename auxB::state stateB;
	typedef typename add_trans<typename auxB::fsm, stateA, Char, stateB>::type new_fsm;
      public:
	typedef typename list::make<new_fsm, new_groups>::type type;
      };

      template <typename Group, typename Char, typename Accu>
      class add_det_trans_fold {
      public:
	typedef typename add_det_trans<typename get<Accu, int_<0> >::type,
				       typename get<Accu, int_<1> >::type,
				       Group,
				       Char>::type type;
      };

      template <typename DFsm, typename Groups, typename Group>
      class add_group {
	typedef typename get_transitions<Group>::type chars;
      public:
	typedef typename fold<bind<quote<add_det_trans_fold>, int_<0>, Group>,
			      chars,
			      tuple<DFsm, Groups> >::type type;
      };

      template <typename Group, typename Accu>
      class add_group_fold {
      public:
	typedef typename add_group<typename get<Accu, int_<0> >::type,
				   typename get<Accu, int_<1> >::type,
				   Group>::type type;
      };

      template <typename Groups, typename Accu>
      class add_groups {
	typedef typename fold<quote<add_group_fold>,
			      Groups,
			      Accu>::type tmp1;
	typedef typename get<tmp1, int_<0> >::type new_fsm;
	typedef typename get<tmp1, int_<1> >::type new_groups;
	typedef typename get<Accu, int_<1> >::type old_groups;
	typedef bind<quote<get>, int_<1>, int_<0> > get_group;
	typedef typename filter<compose<quote<not_>,
					bind<quote<member>,
					     int_<1>,
					     typename map<get_group, old_groups>::type> >,
				typename map<get_group, new_groups>::type>::type created_groups;

      public:
	typedef typename if_<typename is_same<created_groups, nil>::type,
			     wrap<tmp1>,
			     add_groups<created_groups,
					tuple<new_fsm, new_groups> > >::type::type type;
      };

      typedef typename add_groups<cons<typename closure<Fsm,
							epsilon,
							cons<typename Fsm::initial, nil> >::type,
				       nil>,
				  tuple<fsm<nil, int_<0>, int_<0> >, nil> >::type tmp_result;
    public:
      typedef typename set_property<dfsm<typename get<tmp_result, int_<0> >::type::states>,
				    properties::initial, int_<0>,
				    properties::terminal, typename map<bind<quote<get>, int_<1>, int_<1> >,
								       typename filter<compose<bind<quote<member>,
												    int_<0>,
												    typename Fsm::terminal>,
											       bind<quote<get>, int_<1>, int_<0> > >,
										       typename get<tmp_result, int_<1> >::type>::type>::type>::type type;
    };

    template <typename... FsmArgs>
    class get_property<fsm<FsmArgs...>, properties::initial> {
    public:
      typedef typename fsm<FsmArgs...>::initial type;
    };

    template <typename... FsmArgs>
    class get_property<fsm<FsmArgs...>, properties::terminal> {
    public:
      typedef cons<typename fsm<FsmArgs...>::terminal, nil> type;
    };

    namespace __reverse {
      template <typename State, typename Transition, typename Fsm>
      class reverse_trans {
      public:
	typedef typename add_trans<Fsm,
				   typename Transition::state,
				   typename Transition::character,
				   State>::type type;
      };

      template <typename State, typename Fsm>
      class reverse_state {
      public:
	typedef typename fold<bind<quote<reverse_trans>, int_<0>, typename State::id>,
			      typename State::transitions,
			      Fsm>::type type;
      };

      template <typename Initial, typename State, typename Fsm>
      class add_eps_trans_fold {
      public:
	typedef typename add_eps_trans<typename add_eps_trans<Fsm,
							      State,
							      Initial>::type,
				       Initial,
				       State>::type type;
      };
    }

    template <typename Fsm>
    class non_deterministic {
    public:
      typedef Fsm type;
    };

    template <typename States, typename Properties>
    class non_deterministic<dfsm<States, Properties> > {
    public:
      typedef typename length<States>::type nbstates;
      typedef nbstates terminal;
      typedef typename fold<bind<quote<__reverse::add_eps_trans_fold>,
				 int_<0>,
				 terminal>,
			    typename get_property<dfsm<States, Properties>,
						  properties::terminal>::type,
			    typename new_states<fsm<States,
						    int_<0>,
						    int_<0> >,
						int_<1> >::type>::type tmp;

    public:
      typedef fsm<typename tmp::states,
		  typename get_property<dfsm<States, Properties>,
					properties::initial>::type,
		  terminal> type;
    };

    template <typename Fsm>
    class reverse {
      typedef typename length<typename Fsm::states>::type nbstates;
      typedef typename fold<quote<__reverse::reverse_state>,
			    typename Fsm::states,
			    typename new_states<fsm<nil, int_<0>, int_<0> >,
						nbstates>::type>::type reversed;
      typedef nbstates initial;
      typedef typename new_states<reversed, int_<1> >::type reversedi;
      typedef typename fold<bind<quote<__reverse::add_eps_trans_fold>,
				 int_<0>,
				 initial>,
			    typename get_property<Fsm, properties::terminal>::type,
			    reversedi>::type reversedii;

    public:
      typedef fsm<typename reversedii::states,
		  initial,
		  typename get_property<Fsm, properties::initial>::type> type;
    };

    template <typename Fsm>
    class minimal {
    public:
      typedef typename deterministic<typename reverse<typename deterministic<typename reverse<Fsm>::type>::type>::type>::type type;
    };

    namespace operators {
      template <typename... Fsm1, typename... Fsm2>
      typename fsm_or<fsm<Fsm1...>, fsm<Fsm2...> >::type
      operator|(fsm<Fsm1...>, fsm<Fsm2...>) {}

      template <typename... Fsm1, typename... Fsm2>
      typename fsm_seq<fsm<Fsm1...>, fsm<Fsm2...> >::type
      operator>>(fsm<Fsm1...>, fsm<Fsm2...>) {}

      template <typename... Fsm>
      typename fsm_star<fsm<Fsm...> >::type
      operator*(fsm<Fsm...>) {}

      template <typename... Fsm>
      typename non_deterministic<typename minimal<fsm<Fsm...> >::type>::type
      operator!(fsm<Fsm...>) {}
    }

    namespace predefined {
      using namespace operators;
      typedef decltype(!fsm_range<'0','9'>::type()) digit;
      typedef decltype(!*digit()) integer;
      typedef decltype(!(*digit() >> fsm_char<','>::type() >> *digit())) floating;
      typedef decltype(!fsm_or<integer,floating>::type()) number;
      //typedef decltype(!fsm_range<'a','z'>::type()) alpha;
      //typedef decltype(!fsm_range<'A','Z'>::type()) ALPHA;
      //typedef decltype(!fsm_or<ALPHA,alpha>::type()) Alpha;
    }
  }
}

#endif
