/// Reduces actions dispatched for the admin store.
/**
 * Reduces the actions dispatched with the intention of modifying
 * admin data within the store.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file adminReducer.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import {  /// User action types.
  GET_ADMINS,
  CREATE_ADMIN,
  UPDATE_ADMIN,
  REMOVE_ADMIN } from "../actions/types";


const initialState = {  /// Defaults to the guest user.
  currUser: 0,
  admins: {
    0: {
      username: 'guest',
      name: 'Guest',
    },
    1: {
      username: 'vsagrawal',
      name: 'Vaniya'
    }
  }
}

/// Main reducer for user actions.
/**
 * Uses a switch statement to modify the admin store. Switch statement is used
 * to determine which action has been dispatched and to modify the store accordingly.
 *
 * IMPORTANT!! The store is IMMUTABLE. ALL cases must return a COPY of the store,
 * they must not change the store itself. Utilize a return statement and the spread
 * operator (ex.: ...state) to accomplish this.
 *
 * @param state The current state of the data.
 * @param action  The action that is dispatched. Contains a type and a payload.
 * @returns object  A copy of the store, modified according to the action type and payload.
 */
export default (state = initialState, action) => {
  switch(action.type) {
    case GET_ADMINS:
      return {
        ...state
      };
    case CREATE_ADMIN:
      return {
        ...state,
      }
    case UPDATE_ADMIN:
      return {
        ...state,
      };
    case REMOVE_ADMIN:
      return {
        ...state,
      };
    default:
      return state;
  }
}